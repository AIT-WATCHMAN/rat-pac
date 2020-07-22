// This script is use to calculate PMT time residuals distribution. 
// As an argument, use a root file with 5 MeV electrons simulated inside the detector voulme.
// > .L timeResiduals.C
// > timeResiduals("simulated_5MeV_el.root")
// As an output timeRes.root is created, which can be used as an input for Likelihood evaluation
// NOTE: In order to create input for create_like.cc, the x axis has to be reversed and bin content has to be >= 1e-4. Also, fitting a function to time residuals distribution in order to remove statistical fluctuations is recomended.
// Kat

#include <iostream>
#include <iomanip>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <vector>
#include <TH1D.h>


void timeResiduals(const char *file) {
    
<<<<<<< HEAD
    TH1D *timeRes = new TH1D("timeRes","time residuals",550,-20,230);
=======
    Double_t light_vel = 21.8; // [cm/ns] this velocity was calulated for gd-water, and 20x20m tank size, might need adjustment 
    TH1D *timeRes = new TH1D("timeRes","time residuals",1625,-50,600); // 0.4 ns bins
>>>>>>> 3d334653775ac026959bb9b7050f860931ca1db4
    timeRes->SetXTitle("time [ns]");
    
    RAT::DS::Root *rds = new RAT::DS::Root();
    
    TFile *f = new TFile(file);
    TTree *T = (TTree*) f->Get("T");
    T->SetBranchAddress("ds", &rds);
    
    Double_t v_x,v_y,v_z,p_x,p_y,p_z,v_t,p_t,t_t;
    // v_ : vertex_
    // p_ : pmt_
    // t_ : trigger
    // x,y,z,t : 3d position,time
    
    TTree *runT = (TTree*) f->Get("runT");
    //Giving up doing it properly and cheating
    runT->Draw("pmtinfo.pos.X():pmtinfo.pos.Y():pmtinfo.pos.Z():pmtinfo.type","Entry$>-1","goff");
    
    Double_t *x = runT->GetV1();
    Double_t *y = runT->GetV2();
    Double_t *z = runT->GetV3();
    Double_t *typ = runT->GetV4();
    
    for (int i = 0; i < tree->GetEntries(); i++) {

        T->GetEntry(i);
        RAT::DS::MC *mc = rds->GetMC();
        RAT::DS::MCParticle *prim = mc->GetMCParticle(0); // Find position of vertext

        v_x    = prim->GetPosition().X();
        v_y    = prim->GetPosition().Y();
        v_z    = prim->GetPosition().Z();

        //Find out how many subevents:
        Int_t subevents = rds->GetEVCount();
        for (int k = 0; k<subevents; k++) {
            
            RAT::DS::EV *ev = rds->GetEV(k);
            if(ev->GetPMTCount() < 4) continue;  // suggested by Michael Smy

<<<<<<< HEAD
            for (int j = 0; j<ev->GetPMTCount();j++) {
                if(ev->GetPMTCount() < 4) continue; 
		RAT::DS::PMT *pmt = ev->GetPMT(j);
=======
	    for (int j = 0; j<ev->GetPMTCount();j++) {
                RAT::DS::PMT *pmt = ev->GetPMT(j);
>>>>>>> 3d334653775ac026959bb9b7050f860931ca1db4
                t_t = ev->GetCalibratedTriggerTime();
                
                p_x = x[pmt->GetID()];
                p_y = y[pmt->GetID()];
                p_z = z[pmt->GetID()];
                
<<<<<<< HEAD
                v_t = sqrt(pow(p_x-v_x,2)+pow(p_y-v_y,2)+pow(p_z-v_z,2)) / (21.8*10); //c (m/ns * mm/m *index refraction)
=======
                v_t = sqrt(pow(p_x-v_x,2)+pow(p_y-v_y,2)+pow(p_z-v_z,2)) / (light_vel*10.); // cm -> mm, light velocity might need adjustment for medium diffrent than gd-water, or size different then baseline design (20x20m)
>>>>>>> 3d334653775ac026959bb9b7050f860931ca1db4
                p_t = pmt->GetTime() + t_t;
//                printf("%f %f\n",v_t,p_t);
                if(typ[pmt->GetID()]==1)  timeRes->Fill(p_t-v_t); // only ID PMTs
                
            }
            
            
        }
        
    }
<<<<<<< HEAD
=======
    Double_t scal = timeRes->GetMaximum();
    timeRes->Scale(1./scal);
>>>>>>> 3d334653775ac026959bb9b7050f860931ca1db4
    timeRes->SaveAs("timeRes.root");
    timeRes->Delete();
}
