#include <iostream>
#include <iomanip>

using namespace std;

#include <RAT/DS/Run.hh>
#include <RAT/DS/PMTInfo.hh>
#include <RAT/DS/Root.hh>
#include <RAT/DS/MC.hh>
#include <RAT/DS/MCParticle.hh>
#include <RAT/DS/EV.hh>
#include <RAT/DS/PMT.hh>
#include <RAT/DS/PathFit.hh>
#include <RAT/DS/BonsaiFit.hh>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TApplication.h>
#include <TMath.h>

#include <TRandom.h>

#include <pmt_geometry.h>
#include <goodness.h>
#include <searchgrid.h>
#include <fourhitgrid.h>

//Need to seperate the Inner-Detector tubes from the Outer-Detector tubes
static const int innerPMTcode = 1;
static const int vetoPMTcode  = 2;

extern "C"{
void lfariadne_(float *av,int *anhit,float *apmt,float *adir, float *amsg, float *aratio,int *anscat,float *acosscat);
}

int nwin(RAT::DS::PMTInfo *pmtinfo,
	 float twin,float *v,int nfit, int *cfit, float *tfit, int *cwin);


int main(int argc, char **argv)
{
  float darkNoise,offsetT,minT, maxT;
  int nsct;
  int crash_count=0;
  int tot_inner,tot_veto,id;

  printf("\n\nWelcome to BONSAI. The function can take no less than two input and up\n");
  printf("to 6 inputs: infile,outfile,darkNoise,timeOffset,minTime,maxtime\n\n");
  printf("%d input arguments in function bonsai.\n",argc);

  // check if minimum arguments exist
  if (argc<3)
    {
      printf("Less than the required number of arguments\n");
      return -1;
    }
  // set default values
  darkNoise = 10000.; 
  offsetT   = 800.;
  minT      = -500.;
  maxT      = 1000.;
  switch(argc)
    {
    case 3:
      printf("Only input file and output file are provided. All other values set to default.\n");
      break;
    case 4:
      printf("Only input file and output file and dark noise rate are provided. All other values set to default.\n");
      darkNoise = float(strtol(argv[3],NULL,10));  
      break;
    case 5:
      // printf("Only input file and output file are provide. All other values set to default.\n");
      darkNoise = float(strtol(argv[3],NULL,10));
      offsetT   = float(strtol(argv[4],NULL,10));
      break;
    case 6:
      // printf("Only input file and output file are provided. All other values set to default.\n");
      darkNoise = float(strtol(argv[3],NULL,10));
      offsetT   = float(strtol(argv[4],NULL,10));
      minT      = float(strtol(argv[5],NULL,10));
      break;
    case 7:
      // printf("Only input file and output file are provide. All other values set to default.\n");
      darkNoise = float(strtol(argv[3],NULL,10));
      offsetT   = float(strtol(argv[4],NULL,10));
      minT      = float(strtol(argv[5],NULL,10));
      maxT      = float(strtol(argv[6],NULL,10));
      break;
    }
  printf("\n\nUsing:\n");
  printf("(1) Infile \t%20s\n",argv[1]); printf("(2) Outfile \t%20s\n",argv[2]);
  printf("(3) darkNoise \t%20.1f\n", darkNoise); printf("(4) offsetT \t%20.1f\n",offsetT);
  printf("(5) minT \t%20.1f\n",minT); printf("(6) maxT  \t%20.1f\n\n",maxT);

  Int_t    gtid=0, mcid=0,tot_nhit=0, nhits=0, veto_hit=0, particleCountMC=0;
  Int_t    timestamp_ns=0, timestamp_s=0, code=0,old_t_s,old_t_ns,dt1_s=0;
  Int_t    dt1_ns=0, totVHIT=0,inner_hit=0;
  Double_t totPE=0., n9=0., bonsai_goodness=0., dir_goodness=0.;
  Double_t x=0., y=0., z=0., tim=0., u=0., v=0., w=0.;
  Double_t mc_x=0., mc_y=0., mc_z=0., mc_tim=0., mc_u=0., mc_v=0., mc_w=0.;
  Double_t closestPMT=0.,mc_energy=0.;
  Double_t dxx=0.,dyy=0.,dzz=0.,dxmcx=0.,dymcy=0.,dzmcz=0.,dt1=0.,dt0=0.;
  Double_t prev_x = -1e9,prev_y= -1e9,prev_z= -1e9, old_t,p2W,p2ToB;
  Int_t sub_event_tally[20] = {};
  Double_t pmtBoundR=0.,pmtBoundZ=0.;

  // dark noise stuff
  TRandom rnd;
  int npmt;
  float darkrate,tmin,tmax;
  int ndark,darkhit;
  int vhit;

  // Ariadne stuff
  float adir[3],agoodn,aqual,cosscat;

  // root stuff
  TFile *f;
  TTree *rat_tree,*run_tree,*data;
  Int_t n_events;
  TTree *run_summary;

  // rat stuff
  RAT::DS::Root *ds=new RAT::DS::Root();
  RAT::DS::Run  *run=new RAT::DS::Run();
  RAT::DS::EV *ev;
  RAT::DS::PMTInfo *pmtinfo;
  RAT::DS::MC *mc;
  RAT::DS::MCParticle *prim;
  RAT::DS::PMT *pmt;


  // BONSAI stuff
  fit_param   bspar;
  bonsaifit   *bsfit;
  pmt_geometry *bsgeom;
  likelihood  *bslike;
  goodness    *bsgdn;
  fourhitgrid *bsgrid;
  int         cables[5000],veto_cables[5000];
  int	      cables_win[500],veto_cables_win[5000];
  float       times[5000],veto_times[5000];
  float       charges[5000],veto_charges[5000];
  int         event,sub_event,n,count;
  int         inpmt;
  int         hit,nhit,veto_count;
  float       bonsai_vtxfit[4];
  float       goodn[2];
  
  // open input file
  f= new TFile(argv[1]);

  rat_tree=(TTree*) f->Get("T");
  rat_tree->SetBranchAddress("ds", &ds);
  run_tree=(TTree*) f->Get("runT");
  if (rat_tree==0x0 || run_tree==0x0)
    {
      printf("can't find trees T and runT in this file\n");
      return -1;
    }
  run_tree->SetBranchAddress("run", &run);
  if (run_tree->GetEntries() != 1)
    {
      printf("More than one run! abort...\n");
      return -1;
    }

  // open output file
  TFile *out=new TFile(argv[2],"RECREATE");

  data=new TTree("data","low-energy detector triggered events");

  //Define the Integer Tree Leaves
  data->Branch("gtid",&gtid,"gtid/I");
  data->Branch("mcid",&mcid,"mcid/I");
  data->Branch("nhit",&nhits,"nhit/I");
  data->Branch("timestamp_s",&timestamp_s,"timestamp_s/I");
  data->Branch("timestamp_ns",&timestamp_ns,"timestamp_ns/I");
  data->Branch("inner_hit",&inner_hit,"inner_hit/I");//inner detector    
  data->Branch("id_plus_dr_hit",&tot_nhit,"id_plus_dr_hit/I");//Inner detector plus dark rate hits
  data->Branch("veto_hit",&veto_hit,"veto_hit/I");//veto detector
  data->Branch("veto_plus_dr_hit",&totVHIT,"veto_plus_dr_hit/I");//veto detector plus dark rate hits  
  //Define the double Tree Leaves
  data->Branch("pe",&totPE,"pe/D");
  data->Branch("n9",&n9,"n9/D");
  data->Branch("good_pos",&bonsai_goodness,"good_pos/D");
  data->Branch("good_dir",&dir_goodness,"good_dir/D");
  data->Branch("x",&x,"x/D"); data->Branch("y",&y,"y/D");
  data->Branch("z",&z,"z/D"); data->Branch("t",&tim,"t/D");
  data->Branch("u",&u,"u/D"); data->Branch("v",&v,"v/D");
  data->Branch("w",&w,"w/D");
  data->Branch("particleCountMC",&particleCountMC ,"particleCountMC/I");
  data->Branch("mc_energy",&mc_energy,"mc_energy/D");
  data->Branch("mcx",&mc_x,"mcx/D"); data->Branch("mcy",&mc_y,"mcy/D");
  data->Branch("mcz",&mc_z,"mcz/D"); data->Branch("mct",&mc_tim,"mct/D");
  data->Branch("mcu",&mc_u,"mcu/D"); data->Branch("mcv",&mc_v,"mcv/D");
  data->Branch("mcw",&mc_w,"mcw/D");
  // data->Branch("code",&code,"code/I");
  data->Branch("closestPMT",&closestPMT,"closestPMT/D");//Proximity to PMT wall
  data->Branch("dxPrevx",&dxx,"dxPrevx/D");
  data->Branch("dyPrevy",&dyy,"dyPrevy/D");
  data->Branch("dzPrevz",&dzz,"dzPrevz/D");
  data->Branch("dxmcx",&dxmcx,"dxmcx/D");
  data->Branch("dymcy",&dymcy,"dymcy/D");
  data->Branch("dzmcz",&dzmcz,"dzmcz/D");
  data->Branch("dt",&dt1,"dt/D");  data->Branch("dt_s",&dt1_s,"dt_s/I");
  data->Branch("dt_ns",&dt1_ns,"dt_ns/I"); data->Branch("dt0",&dt0,"dt0/D");

  Int_t n_inner_pmts,radius,theta_tmp,phi_tmp;
 
  data->Branch("n_inner_pmts",&n_inner_pmts,"n_inner_pmts/I");
  Double_t theta_pmt[6000],z_pmt[6000],radius_pmt[6000],u_pmt[6000],v_pmt[6000],q_pmt[6000],t_pmt[6000];
  data->Branch("theta_pmt",theta_pmt,"theta_pmt[n_inner_pmts]/D");
  data->Branch("z_pmt",z_pmt,"z_pmt[n_inner_pmts]/D");
  data->Branch("radius_pmt",radius_pmt,"radius_pmt[n_inner_pmts]/D");
  data->Branch("u_pmt",u_pmt,"u_pmt[n_inner_pmts]/D");
  data->Branch("v_pmt",v_pmt,"v_pmt[n_inner_pmts]/D");
  data->Branch("q_pmt",q_pmt,"q_pmt[n_inner_pmts]/D");
  data->Branch("t_pmt",t_pmt,"t_pmt[n_inner_pmts]/D");

  Double_t u_pmt_ref[6000],v_pmt_ref[6000];
  Int_t n_inner_pmts_ref;
  run_summary=new TTree("runSummary","mc run summary");
  run_summary->Branch("nEvents",&n_events,"nEvents/I");
  run_summary->Branch("subEventTally",sub_event_tally,"subEventTally[20]/I");
  run_summary->Branch("n_inner_pmts_ref",&n_inner_pmts_ref,"n_inner_pmts_ref/I");

  run_summary->Branch("u_pmt_ref",u_pmt_ref,"u_pmt_ref[n_inner_pmts_ref]/D");
  run_summary->Branch("v_pmt_ref",v_pmt_ref,"v_pmt_ref[n_inner_pmts_ref]/D");
  run_tree->GetEntry(0);

  // loop over PMTs and find positions and location of PMT support
  pmtinfo=run->GetPMTInfo();
  n=pmtinfo->GetPMTCount();
  tot_inner = 0; tot_veto =0;
 
  //Determines the number of inner and veto pmts
  for(hit=count=0; hit<n; hit++)
    {
      if (pmtinfo->GetType(hit)==innerPMTcode)     ++tot_inner;
      else if (pmtinfo->GetType(hit)==vetoPMTcode) ++tot_veto;
      else
	printf("PMT does not have valid identifier: %d \n",
	       pmtinfo->GetType(hit));
    }
  if (n != (tot_inner+tot_veto))
    printf("Mis-match in total PMT numbers: %d, %d \n",n, tot_inner+tot_veto);
    
  inpmt= tot_inner;

  // generate BONSAI geometry object
  {
    float xyz[3*inpmt+1];

    printf("In total there are  %d PMTs in WATCHMAN\n",n);
    n_inner_pmts = 0;    
    for(hit=0; hit<n; hit++)
      {
	if(pmtinfo->GetType(hit)==innerPMTcode)
	  {
	    TVector3 pos=pmtinfo->GetPosition(hit);
	    xyz[3*count]=pos[0]*0.1;
	    xyz[3*count+1]=pos[1]*0.1;
	    xyz[3*count+2]=pos[2]*0.1;
        
            
	    if (pos[0]>pmtBoundR) pmtBoundR = pos[0];
	    if (pos[2]>pmtBoundZ) pmtBoundZ = pos[2];
	    ++count;
	  }
      }
      n_inner_pmts_ref = 0;
      for(hit=0; hit<n; hit++)
      {
        if(pmtinfo->GetType(hit)==innerPMTcode)
          {
                  TVector3 npos=pmtinfo->GetPosition(hit);

                  radius_pmt[n_inner_pmts_ref] = TMath::Sqrt(npos.X()*npos.X() + npos.Y()*npos.Y())/pmtBoundR;
                  theta_pmt[n_inner_pmts_ref] = TMath::ATan2(npos.X(),npos.Y());
                  z_pmt[n_inner_pmts_ref] = npos.Z()/pmtBoundZ;
                  if(z_pmt[n_inner_pmts_ref] == 1.){
                     u_pmt_ref[n_inner_pmts_ref] = npos.X()/pmtBoundR;
                     v_pmt_ref[n_inner_pmts_ref] = 2.-npos.Y()/pmtBoundR;
                   } else if(z_pmt[n_inner_pmts_ref] == -1.){
                     u_pmt_ref[n_inner_pmts_ref] = npos.X()/pmtBoundR;
                     v_pmt_ref[n_inner_pmts_ref] = -2.-npos.Y()/pmtBoundR;
                   } else{
                      u_pmt_ref[n_inner_pmts_ref] = theta_pmt[n_inner_pmts_ref];
                      v_pmt_ref[n_inner_pmts_ref] = z_pmt[n_inner_pmts_ref];
                   }
                   n_inner_pmts_ref += 1 ;
 	}
    }
    printf("There are %d inner pmts and %d veto pmts \n ",tot_inner,tot_veto);
    printf("Inner PMT boundary (r,z):(%4.1f mm %4.1f, mm)\n",pmtBoundR,pmtBoundZ);

    if (count!= tot_inner)
      printf("There is a descreptancy in inner PMTS %d vs %d",count,tot_inner);

    // create BONSAI objects from the PMT position array
    bsgeom=new pmt_geometry(inpmt,xyz);
    bslike=new likelihood(bsgeom->cylinder_radius(),bsgeom->cylinder_height());
    bsfit=new bonsaifit(bslike);
  }

  n_events = rat_tree->GetEntries();
  //run_summary->Fill();

  // loop over all events
  for (event = 0; event < n_events; event++)
    {
      if (event%1000==0)
	printf("Evaluating event %d of %d (%d sub events)\n",event,n_events,
	       ds->GetEVCount());
      rat_tree->GetEntry(event);

      sub_event_tally[ds->GetEVCount()]++;
      // loop over all subevents
      for(sub_event=0;sub_event<ds->GetEVCount();sub_event++)
	{
	  gtid +=1;
	  mcid = event;
     
	  ev = ds->GetEV(sub_event);
	  totPE = ev->GetTotalCharge();
	  //something is fishy with this time
	  timestamp_s = ev->GetUTC().GetSec();
	  timestamp_ns = ev->GetUTC().GetNanoSec();

	  TVector3 temp;
      
	  mc = ds->GetMC();
	  prim = mc->GetMCParticle(0);
	  mc_energy                   = prim->GetKE();
	  temp = prim->GetPosition();
	  mc_x = temp.X();
	  mc_y = temp.Y();
	  mc_z = temp.Z();
	  mc_tim = prim->GetTime();//200 offset
	  mc_tim = prim->GetTime()-ev->GetDeltaT();//200 offset

	  nhit=ev->GetPMTCount();
	  // loop over all PMT hits for each subevent
	  n_inner_pmts = 0;
	  for(hit=count=veto_count=0; hit<nhit; hit++)
	    {
	      pmt=ev->GetPMT(hit);
	      id = pmt->GetID();
              
          
	      //only use information from the inner pmts
	      if(pmtinfo->GetType(id) == innerPMTcode)
		{
		  cables[count]=pmt->GetID()+1;
		  times[count]=pmt->GetTime()+offsetT;
		  charges[count]=pmt->GetCharge();
                  t_pmt[n_inner_pmts] = pmt->GetTime();
                  q_pmt[n_inner_pmts] = pmt->GetCharge();
                  TVector3 npos=pmtinfo->GetPosition(pmt->GetID());
		  count++;
                  radius_pmt[n_inner_pmts] = TMath::Sqrt(npos.X()*npos.X() + npos.Y()*npos.Y())/pmtBoundR;
                  theta_pmt[n_inner_pmts] = TMath::ATan2(npos.X(),npos.Y());       
                  z_pmt[n_inner_pmts] = npos.Z()/pmtBoundZ;
                  if(z_pmt[n_inner_pmts] == 1.){
                     u_pmt[n_inner_pmts] = npos.X()/pmtBoundR;
                     v_pmt[n_inner_pmts] = 2.-npos.Y()/pmtBoundR;
                   } else if(z_pmt[n_inner_pmts] == -1.){
                     u_pmt[n_inner_pmts] = npos.X()/pmtBoundR;
                     v_pmt[n_inner_pmts] = -2.+npos.Y()/pmtBoundR;
                   } else{
                      u_pmt[n_inner_pmts] = theta_pmt[n_inner_pmts];
                      v_pmt[n_inner_pmts] = z_pmt[n_inner_pmts];
                   }
                   n_inner_pmts += 1 ;
		}
	      else if(pmtinfo->GetType(id)== vetoPMTcode)
		{
		  veto_cables[veto_count]=pmt->GetID()+1;
		  veto_times[veto_count]=pmt->GetTime()+offsetT;
		  veto_charges[veto_count]=pmt->GetCharge();
		  veto_count++;
		}
	      else
		printf("Unidentified PMT type: (%d,%d) \n",count,pmtinfo->GetType(id));
	    } // end of loop over all PMT hits
	  veto_hit = veto_count;
	  inner_hit = count;
	  nhit = count;

	  //Inner PMT Dark Rate
	  npmt=tot_inner;
	  darkrate=darkNoise*npmt;
	  tmin=minT+offsetT;
	  tmax= maxT+offsetT;
	  ndark=rnd.Poisson((tmax-tmin)*1e-9*darkrate);

	  //int inhit= count;
	  //loop over (randomly generated) dark hits and
	  //assign random dark rate where event rate is 
	  //below dark rate for the inner detector
	  for(darkhit=0; darkhit<ndark; darkhit++)
	    {
	      int darkcable= (int)(npmt*rnd.Rndm()+1);
	      float darkt=tmin+(tmax-tmin)*rnd.Rndm();
	      // loop over all inner PMT hits
	      for(hit=0; hit<nhit; hit++)
		if (cables[hit]==darkcable) break;
	      if (hit==nhit)
		{
		  cables[hit]=darkcable;
		  times[hit]=darkt;
		  charges[hit]=1;
		  nhit++;
		} 
	      else
		{
		  if (darkt<times[hit]) times[hit]=darkt;
		  charges[hit]++;
		} //end of loop over all inner  PMT hits
	    } // end of loop over inner dark hits
	  //Veto PMT
	  //Inner PMT Dark Rate
      
	  npmt=tot_veto;
	  darkrate=darkNoise*npmt;
	  ndark=rnd.Poisson((tmax-tmin)*1e-9*darkrate);
	  vhit= veto_count;
      //loop over (randomly generated) dark hits and
      //assign random dark rate where event rate is
      //below dark rate for the veto detector
	  for(darkhit=0; darkhit<ndark; darkhit++)
	    {
	      int darkcable=(int) (npmt*rnd.Rndm()+1);
	      float darkt=tmin+(tmax-tmin)*rnd.Rndm();
        // loop over all inner PMT hits
	      for(hit=0; hit<vhit; hit++)
		if (veto_cables[hit]==darkcable) break;
	      if (hit==vhit)
		{
		  veto_cables[hit]=darkcable;
		  veto_times[hit]=darkt;
		  veto_charges[hit]=1;
		  vhit++;
		}
	      else
		{
		  if (darkt<veto_times[hit]) veto_times[hit]=darkt;
		  veto_charges[hit]++;
		} //end of loop over all veto  PMT hits
	    } // end of loop over vetp dark hits 
	  totVHIT= vhit;
	  tot_nhit= nhit;
	  //Determines how many events before crash
	  crash_count++;
/*
	  // generate BONSAI objects
	  bsgdn=new goodness(bslike->sets(),bslike->chargebins(),
			     bsgeom,nhit,cables,times,charges);
	  bsgrid=new fourhitgrid(bsgeom->cylinder_radius(),
				 bsgeom->cylinder_height(),bsgdn);
	  bslike->set_hits(bsgdn);
	  // fit
	  bslike->maximize(bsfit,bsgrid);

	  x= 10.*bsfit->xfit();y= 10.*bsfit->yfit();z= 10.*bsfit->zfit();
     
	  // calculate n9 and goodness
	  *bonsai_vtxfit=bsfit->xfit();
	  bonsai_vtxfit[1]=bsfit->yfit();
	  bonsai_vtxfit[2]=bsfit->zfit();
	  n9 =  bslike->nwind(bonsai_vtxfit,-3,6);
	  bslike->tgood(bonsai_vtxfit,0,goodn[0]);
	  tim=bslike->get_zero()-offsetT;

	  // delete BONSAI objects and reset likelihoods
	  delete bsgrid;
	  delete bsgdn;
	  bslike->set_hits(NULL);

	  // get momentum vector and normalize it
	  temp = prim->GetMomentum();
	  temp = temp.Unit();
	  mc_u = temp.X();mc_v = temp.Y();mc_w = temp.Z();

	  tot_nhit = nhit;

	  // get distance and time difference to previous fit event
	  dxx = x-prev_x;dyy = y-prev_y;dzz = z-prev_z;
	  if(dxx>1e6)
	    {
	      dxx = 0.;dyy = 0.;dzz = 0.;
	    }
	  dxmcx = x-mc_x;dymcy = y-mc_y;dzmcz = z-mc_z;
	  dt1_s = timestamp_s - old_t_s;
	  dt1_ns = timestamp_ns - old_t_ns;

	  // calculate smallest distance to any pmt
	  p2W = pmtBoundR-sqrt(x*x+y*y);
	  p2ToB = pmtBoundZ-sqrt(z*z);
	  closestPMT = TMath::Min(p2W,p2ToB);

	  dt1 = ev->GetCalibratedTriggerTime();
	  dt0 = bslike->get_zero()-offsetT;
	  prev_x=x;prev_y=y;prev_z=z;
	  old_t = double(timestamp_s)+double(timestamp_ns)/1e9;
	  old_t_s =  timestamp_s;
	  old_t_ns =  timestamp_ns;

	  // do direction fit
	  bonsai_goodness = goodn[0];
	  // find all PMTs within 9 nsec window
	  int n9win=nwin(pmtinfo,9,bonsai_vtxfit,nhit,cables,times,cables_win);
	  float apmt[3*n9win];
	  // fill PMT positions into an array
	  //n_inner_pmts = 0;
	  for(hit=0; hit<n9win; hit++)
	    {
	      TVector3 n9pos=pmtinfo->GetPosition(cables_win[hit]-1);
	      apmt[3*hit]=n9pos.X()*0.1;
	      apmt[3*hit+1]=n9pos.Y()*0.1;
	      apmt[3*hit+2]=n9pos.Z()*0.1;
	    }
	  // call direction fit and save results
	  lfariadne_(bonsai_vtxfit,&n9win,apmt,
		     adir,&agoodn,&aqual,&nsct,&cosscat);
	  dir_goodness = agoodn;
	  u=adir[0];
	  v=adir[1];
	  w=adir[2];*/
	  data->Fill();
	} 
    }
  out->cd();
  data->Write();
  run_summary->Fill();
  run_summary->Write();
  out->Close();
  delete(bsfit);
  delete(bslike);
  delete(bsgeom);
  return 0;
}

int nwin(RAT::DS::PMTInfo *pmtinfo,
         float twin,float *v,int nfit,int *cfit,float *tfit,int *cwin)
{
    if (nfit<=0) return(0);

    float ttof[nfit],tsort[nfit],dx,dy,dz;
    int   hit,nwin=0,nwindow,hstart_test,hstart,hstop;

    // calculate t-tof for each hit
    for(hit=0; hit<nfit; hit++)
    {
        TVector3 pos=pmtinfo->GetPosition(cfit[hit]-1);
        dx=pos.X()*0.1-v[0];
        dy=pos.Y()*0.1-v[1];
        dz=pos.Z()*0.1-v[2];
        tsort[hit]=ttof[hit]=tfit[hit]-sqrt(dx*dx+dy*dy+dz*dz)*CM_TO_NS;
    }
    sort(tsort,tsort+nfit);

    // find the largest number of hits in a time window <= twin
    nwindow=1;
    hstart_test=hstart=0;
    while(hstart_test<nfit-nwindow)
    {
        hstop=hstart_test+nwindow;
        while((hstop<nfit) && (tsort[hstop]-tsort[hstart_test]<=twin))
        {
            hstart=hstart_test;
            nwindow++;
            hstop++;
        }
        hstart_test++;
    }
    hstop=hstart+nwindow-1;
    for(hit=0; hit<nfit; hit++)
    {
        if (ttof[hit]<tsort[hstart]) continue;
        if (ttof[hit]>tsort[hstop]) continue;
        cwin[nwin++]=cfit[hit];
    }
    if (nwin!=nwindow) printf("nwin error %d!=%d\n",nwin,nwindow);
    return(nwindow);
}

