#include <vector>
#include <RAT/LessSimpleDAQProc.hh>
#include <RAT/DB.hh>
#include <G4ThreeVector.hh>
#include <RAT/DetectorConstruction.hh>
#include <iostream>
using namespace std;

namespace RAT {
    
    LessSimpleDAQProc::LessSimpleDAQProc() : Processor("lesssimpledaq") {
        //DBLinkPtr ldaq = DB::Get()->GetLink("DAQ");
        //fSPECharge = ldaq->GetDArray("SPE_charge"); // convert pC to gain-normalized units
        fEventCounter = 0;
    }
    
    Processor::Result LessSimpleDAQProc::DSEvent(DS::Root *ds) {
        // This simple simulation assumes only tubes hit by a photon register
        // a hit, and that every MC event corresponds to one triggered event
        // The time of the PMT hit is that of the first photon.
        
        DS::MC *mc = ds->GetMC();
        if(ds->ExistEV()) {  // there is already a EV branch present
            ds->PruneEV();     // remove it, otherwise we'll have multiple detector events
            // in this physics event ** we really should warn the user what is taking place
        }
        
        double totalQ = 0.0;
        double pmtQ = 0.0;
        double time,timeTmp;
        int nSubEvents = 0;
        double timeWindow  = 800., oldGroup;
        
        //cout <<"New Event====================================" << endl;
        // First part is to load into vector PMT information for full event
        vector <double> timeAndChargeAndID;
        vector<vector <double> > pmtARRAY;
        //Place the time and charge of a PMT into an matrix
        for (int imcpmt=0; imcpmt < mc->GetMCPMTCount(); imcpmt++) {
            DS::MCPMT *mcpmt = mc->GetMCPMT(imcpmt);
            if (mcpmt->GetMCPhotonCount() > 0) {
                for (int i=0; i < mcpmt->GetMCPhotonCount(); i++)  {
                    timeAndChargeAndID.push_back(mcpmt->GetMCPhoton(i)->GetFrontEndTime());
                    timeAndChargeAndID.push_back(mcpmt->GetMCPhoton(i)->GetCharge());
                    timeAndChargeAndID.push_back(mcpmt->GetID());
                    timeAndChargeAndID.push_back(i);
                    timeAndChargeAndID.push_back(mcpmt->GetMCPhotonCount());
                    timeAndChargeAndID.push_back(mcpmt->GetMCPhoton(i)->GetHitTime());
                    
                    pmtARRAY.push_back(timeAndChargeAndID);
                    timeAndChargeAndID.resize(0);
                    
                    //printf("%4.3e\n",mcpmt->GetMCPhoton(i)->GetFrontEndTime()-mcpmt->GetMCPhoton(i)->GetHitTime());
                    //cout << "(time,charge,id): ("<<mcpmt->GetMCPhoton(i)->GetFrontEndTime()<<","<<mcpmt->GetMCPhoton(i)->GetCharge()<<","<<mcpmt->GetID()<<")"<<endl;
                }
            }
        }
        sort(pmtARRAY.begin(),pmtARRAY.end());
        // Second part is to find cluster times. This is importan for IBD/ neutron capture
        vector <Double_t> clusterTime;
        // Give an unrealistic time to compare to
        clusterTime.push_back(1000000000000000000);
        
        //get the number odd subevent
        //and tally the cluster time of each subevent
        //cout <<"oooooooooooooooo sorted oooooooooooo" << endl;
        for (unsigned long pmtIndex = 0; pmtIndex < pmtARRAY.size(); pmtIndex++) {
            
            //cout << "(time,charge,id): ("<<pmtARRAY[pmtIndex][0]<<","<< pmtARRAY[pmtIndex][1]<< "," << pmtARRAY[pmtIndex][2]<<")"<<endl;
            
            time = pmtARRAY[pmtIndex][0];
            oldGroup = 0;
            timeTmp = 0 ;
            for (unsigned long jj = 0; jj< clusterTime.size();jj++){
                if(fabs(time-clusterTime[jj]) < timeWindow){
                    oldGroup+=1;
                    //This part get called only on second run through
                    if (time < clusterTime[jj]) {
                        clusterTime[jj] = time;
                    }
                }else{
                    timeTmp = time;
                }
            }
            if (oldGroup==0) {
                if(nSubEvents ==0){
                    clusterTime.pop_back();// Remove unrealistic time and provide better alternative
                    clusterTime.push_back(timeTmp);
                }else{
                    clusterTime.push_back(timeTmp);
                }
                //                h2->Fill(timeTmp/1e3);
                //                printf("%lu %f %f %d %lu %3.1f\n",pmtIndex,time, timeTmp,nSubEvents,clusterTime.size(),clusterTime[nSubEvents]);
                nSubEvents+=1;
            }
        }
        // std::sort(clusterTime.begin(), clusterTime.end());
        
        
        
        timeTmp = 0.;
        int oldID = -1;
        
        vector <double> idGroup, tGroup, qGroup;
        bool itsThere;
        int goHere;
        
        for (int kk = 0; kk<nSubEvents; kk++) {
            
            DS::EV *ev = ds->AddNewEV();
            DS::PMT* pmt;
            
            if( kk == 0 ){ ev->SetDeltaT(clusterTime[kk]); }
            else{ ev->SetDeltaT(clusterTime[kk]-clusterTime[kk-1]); }
            
            /*
             if(kk>0){
             ev->SetDeltaT(clusterTime[kk]-clusterTime[kk-1]);
             }
             */
            
            ev->SetCalibratedTriggerTime((clusterTime[kk]));
            ev->SetID(kk);//fEventCounter
            //            ev->SetUniqueID(fEventCounter);
            
            fEventCounter+=1;
            oldID = -1, totalQ = 0.0, pmtQ = 0.0;
            
            for (unsigned long pmtIndex = 0; pmtIndex < pmtARRAY.size(); pmtIndex++) {
                
                time = pmtARRAY[pmtIndex][0];
                
                if (fabs(time-clusterTime[kk]) <400) {
                    
                    /*if (pmtARRAY[pmtIndex][2] != oldID){
                     timeTmp = time;
                     pmt = ev->AddNewPMT();
                     pmt->SetID(int(pmtARRAY[pmtIndex][2]));
                     pmtQ = 0.0;
                     }
                     
                     pmtQ += pmtARRAY[pmtIndex][1];
                     totalQ += pmtARRAY[pmtIndex][1];
                     
                     //Set an offset of 200 ns for the PMT time and have a relative PMT time
                     // Removed offset
                     pmt->SetTime(timeTmp-clusterTime[kk]);
                     pmt->SetCharge(pmtQ);
                     oldID = pmtARRAY[pmtIndex][2];*/
                    
                    //check if the pmt id has existed within a group of subevent
                    itsThere = false;
                    for(unsigned long cc = 0 ; cc < idGroup.size() ; cc++ ){
                        if( pmtARRAY[pmtIndex][2] == idGroup[cc] ){
                            itsThere = true;
                            goHere = cc; break;
                        }
                    }
                    
                    //if the PMT is already in the vector, the find its friend
                    if( itsThere ){ qGroup[ goHere ] += pmtARRAY[pmtIndex][1]; }
                    
                    //if the PMT is not in the vector yet, add it to the vector
                    else{
                        idGroup.push_back( pmtARRAY[pmtIndex][2] );
                        tGroup.push_back ( pmtARRAY[pmtIndex][0] - clusterTime[kk] );
                        qGroup.push_back ( pmtARRAY[pmtIndex][1] );
                    }
                    
                    //accumulate total q within one subevent
                    totalQ += pmtARRAY[pmtIndex][1];
                }
            }
            
            //we can then set these events on the PMT for one subevent
            for( unsigned long dd = 0 ; dd < idGroup.size() ; dd++ ){
                pmt = ev->AddNewPMT();
                pmt->SetID    (  idGroup[dd]   );
                pmt->SetTime  (  tGroup [dd]   );
                pmt->SetCharge(  qGroup [dd]   );
            }
            
            //resize all vectors for the next subevent
            idGroup.resize(0); tGroup.resize(0); qGroup.resize(0);
            
            //regster total charge of one subevent
            ev->SetTotalCharge(totalQ);
        }
        
        return Processor::OK;
    }
    
} // namespace RAT
