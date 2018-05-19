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

#include <TRandom.h>

#include <pmt_geometry.h>
#include <goodness.h>
#include <searchgrid.h>
#include <fourhitgrid.h>
float darkNoise,offsetT,minT, maxT;
float bonsai_vtxfit[4];
float goodn[2];

int main(int argc, char **argv) {
  printf("\n\nWelcome to BONSAI. The function can take no less than two input and up\n");
  printf("to 6 inputs: infile,outfile,darkNoise,timeOffset,minTime,maxtime\n\n");
  printf("%d input arguments in function bonsai.\n",argc);

  if(argc<3){
    printf("Less than the required number of arguments\n");
    return -1;
  }
  else if(argc==3){
    printf("Only input file and output file are provided. All other values set to default.\n");
    darkNoise = 10000.;
    offsetT   = 800.;
    minT      = -500.;
    maxT      = 1000.;
  }else if(argc==4){
    // printf("Only input file and output file are provided. All other values set to default.\n");
    darkNoise = float(strtol(argv[3],NULL,10));
    offsetT   = 800.;
    minT      = -500.;
    maxT      = 1000.;
  }else if(argc==5){
    // printf("Only input file and output file are provide. All other values set to default.\n");
    darkNoise = float(strtol(argv[3],NULL,10));
    offsetT   = float(strtol(argv[4],NULL,10));
    minT      = -500.;
    maxT      = 1000.;
  }else if(argc==6){
    // printf("Only input file and output file are provided. All other values set to default.\n");
    darkNoise = float(strtol(argv[3],NULL,10));
    offsetT   = float(strtol(argv[4],NULL,10));
    minT      = float(strtol(argv[5],NULL,10));
    maxT      = 1000.;
  }else if(argc==7){
    // printf("Only input file and output file are provide. All other values set to default.\n");
    darkNoise = float(strtol(argv[3],NULL,10));
    offsetT   = float(strtol(argv[4],NULL,10));
    minT      = float(strtol(argv[5],NULL,10));
    maxT      = float(strtol(argv[6],NULL,10));
  }
  printf("\n\nUsing:\n");
  printf("(1) Infile \t%20s\n",argv[1]); printf("(2) Outfile \t%20s\n",argv[2]);
  printf("(3) darkNoise \t%20.1f\n", darkNoise); printf("(4) offsetT \t%20.1f\n",offsetT);
  printf("(5) minT \t%20.1f\n",minT); printf("(6) maxT  \t%20.1f\n\n",maxT);

  Int_t  gtid=0, mcid=0,totNHIT=0, nhits=0, od_hit=0, particleCountMC=0,
  timestamp_ns=0, timestamp_s=0, code=0;
  Double_t  totPE=0., n9=0., _goodness=0., _dirGoodness=0., x=0., y=0., z=0.,
  u=0., v=0., w=0., mcX=0., mcY=0., mcZ=0., mcU=0., mcV=0.,
  mcW=0.,closestPMT=0.,mc_energy=0.;
  Double_t dxx=0.,dyy=0.,dzz=0.,dxmcx=0.,dymcy=0.,dzmcz=0.,dt1=0.,dt0=0.;
  Double_t prev_x = -1e9,prev_y= -1e9,prev_z= -1e9, old_t;

  TTree *data = new TTree("data","low-energy detector triggered events");
  //Define the Integer Tree Leaves
  data->Branch("gtid",&gtid,"gitd/I");
  data->Branch("mcid",&mcid,"mcid/I");
  data->Branch("nhit",&nhits,"nhit/I");
  data->Branch("timestamp_s",&timestamp_s,"timestamp_s/I");
  data->Branch("timestamp_ns",&timestamp_ns,"timestamp_ns/I");
  data->Branch("id_plus_dr_hit",&totNHIT,"id_plus_dr_hit/I");//Inner detector plus dark rate hits
  data->Branch("od_hit",&od_hit,"od_hit/I");//Inner detector plus dark rate hits
  //Define the double Tree Leaves
  data->Branch("pe",&totPE,"pe/D");
  data->Branch("n9",&n9,"n9/D");
  data->Branch("good_pos",&_goodness,"good_pos/D");
  data->Branch("good_dir",&_dirGoodness,"good_dir/D");
  data->Branch("x",&x,"x/D"); data->Branch("y",&y,"y/D");
  data->Branch("z",&z,"z/D"); data->Branch("u",&u,"u/D");
  data->Branch("v",&v,"v/D"); data->Branch("w",&w,"w/D");
  data->Branch("particleCountMC",&particleCountMC ,"particleCountMC/I");
  data->Branch("mc_energy",&mc_energy,"mc_energy/D");
  data->Branch("mcx",&mcX,"mcx/D"); data->Branch("mcy",&mcY,"mcy/D");
  data->Branch("mcz",&mcZ,"mcz/D"); data->Branch("mcu",&mcU,"mcu/D");
  data->Branch("mcv",&mcV,"mcv/D"); data->Branch("mcw",&mcW,"mcw/D");
  // data->Branch("code",&code,"code/I");
  data->Branch("closestPMT",&closestPMT,"closestPMT/D");//Proximity to PMT wall
  data->Branch("dxPrevx",&dxx,"dxPrevx/D"); data->Branch("dyPrevy",&dyy,"dyPrevy/D");
  data->Branch("dzPrevz",&dzz,"dzPrevz/D"); data->Branch("dxmcx",&dxmcx,"dxmcx/D");
  data->Branch("dymcy",&dymcy,"dymcy/D"); data->Branch("dzmcz",&dzmcz,"dzmcz/D");
  data->Branch("dt",&dt1,"dt/D"); data->Branch("dt0",&dt0,"dt0/D");

  TFile *f = new TFile(argv[1]);
  TTree *T = (TTree*) f->Get("T");
  TTree *runT = (TTree*) f->Get("runT");
  TFile *out=new TFile(argv[2],"RECREATE");

  TRandom rnd;

  fit_param   bspar;
  bonsaifit   *bsfit;
  pmt_geometry *bsgeom;
  likelihood  *bslike;
  goodness    *bsgdn;
  fourhitgrid *bsgrid;
  int         cables[500];
  float       times[500];
  float       charges[500];

  RAT::DS::Run *run = new RAT::DS::Run();
  runT->SetBranchAddress("run", &run);
  if (runT->GetEntries() != 1) {
    //More than one run! abort...
    return -1;
  }
  runT->GetEntry(0);
  RAT::DS::PMTInfo *pmtinfo = run->GetPMTInfo();

  {
    int   i,n;
    n=pmtinfo->GetPMTCount();
    float xyz[3*n+1];

    printf("have %d PMTs in WATCHMAN\n",n);
    for(i=0; i<n; i++)
    {
      TVector3 pos=pmtinfo->GetPosition(i);
      xyz[3*i]=pos[0]*0.1;
      xyz[3*i+1]=pos[1]*0.1;
      xyz[3*i+2]=pos[2]*0.1;
    }
    bsgeom=new pmt_geometry(n,xyz);
    bslike=new likelihood(bsgeom->cylinder_radius(),bsgeom->cylinder_height());
    bsfit=new bonsaifit(bslike);
  }

  RAT::DS::Root *ds = new RAT::DS::Root();
  T->SetBranchAddress("ds", &ds);

  int nEvents = T->GetEntries();
  vector<double> bx(nEvents), by(nEvents), bz(nEvents), bt(nEvents),
  bdx(nEvents), bdy(nEvents), bdz(nEvents);
  vector<double> px(nEvents), py(nEvents), pz(nEvents), pt(nEvents),
  pdx(nEvents), pdy(nEvents), pdz(nEvents);
  vector<double> mcx(nEvents), mcy(nEvents), mcz(nEvents), mct(nEvents),
  mcdx(nEvents), mcdy(nEvents), mcdz(nEvents);

  for (int i = 0; i < nEvents; i++) {

    // printf("Evaluating event %d of %d (%d)\n",i,nEvents,ds->GetEVCount());
    T->GetEntry(i);

    for(int _ev=0;_ev<ds->GetEVCount();_ev++){
      gtid +=1;
      mcid = i;

      RAT::DS::EV *ev = ds->GetEV(_ev);
      timestamp_s = ev->GetUTC().GetSec();
      timestamp_ns = ev->GetUTC().GetNanoSec();

      TVector3 temp;

      RAT::DS::MC *mc = ds->GetMC();
      RAT::DS::MCParticle *prim = mc->GetMCParticle(0);

      temp = prim->GetPosition();
      mcx[i] = temp.X();
      mcy[i] = temp.Y();
      mcz[i] = temp.Z();
      mct[i] = prim->GetTime();//200 offset
      mct[i] = prim->GetTime()-ev->GetDeltaT();//200 offset

      int hit,nhit=ev->GetPMTCount();
      nhits = nhit;
      for(hit=0; hit<nhit; hit++)
      {
        RAT::DS::PMT *pmt=ev->GetPMT(hit);
        cables[hit]=pmt->GetID()+1;
        times[hit]=pmt->GetTime()+offsetT;
        charges[hit]=pmt->GetCharge();
      }
      int npmt=pmtinfo->GetPMTCount();
      float darkrate=darkNoise*npmt;
      float tmin=minT+offsetT;
      float tmax= maxT+offsetT;
      int ndark,darkhit;
      ndark=rnd.Poisson((tmax-tmin)*1e-9*darkrate);

      for(darkhit=0; darkhit<ndark; darkhit++)
      {
        int darkcable=(int) (npmt*rnd.Rndm()+1);
        float darkt=tmin+(tmax-tmin)*rnd.Rndm();
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
        }
      }
      double dx,dy,dz,dr,dt;
      for(hit=0; hit<nhit; hit++)
      {
        int id=cables[hit]-1;
        TVector3 pos=pmtinfo->GetPosition(id);
        dx=(pos[0]-mcx[i])*0.1;
        dy=(pos[1]-mcy[i])*0.1;
        dz=(pos[2]-mcz[i])*0.1;
        dr=sqrt(dx*dx+dy*dy+dz*dz);
        dt=times[hit]-offsetT-dr/21.8-mct[i];
        // ttof.Fill(dt,1);
        // tofvsdr.Fill(dr,dt,1);//times[hit]-offsetT-mct[i],1);
        // dtvsdr.Fill(dr,dt,1);
      }
      bsgdn=new goodness(bslike->sets(),bslike->chargebins(),
      bsgeom,nhit,cables,times,charges);
      bsgrid=new fourhitgrid(bsgeom->cylinder_radius(),bsgeom->cylinder_height(),
      bsgdn);
      bslike->set_hits(bsgdn);
      bslike->maximize(bsfit,bsgrid);
      // printf("MC %4d: %7.1lf %7.1lf %7.1lf %5.1lf\n",i,
      // mcx[i],mcy[i],mcz[i],mct[i]);
      // printf("BONSAI:  %7.1lf %7.1lf %7.1lf %5.1lf\n",
      // 10*bsfit->xfit(),10*bsfit->yfit(),10*bsfit->zfit(),
      // bslike->get_zero()-offsetT);

      mcX = mcx[i];mcY = mcy[i];mcZ = mcz[i];
      x= 10*bsfit->xfit();y= 10*bsfit->yfit();z= 10*bsfit->zfit();

      dx=10*bsfit->xfit()-mcx[i];
      dy=10*bsfit->yfit()-mcy[i];
      dz=10*bsfit->zfit()-mcz[i];

      // bonsaidx.Fill(dx,1);
      // bonsaidy.Fill(dy,1);
      // bonsaidz.Fill(dz,1);
      // bonsaidr.Fill(sqrt(dx*dx+dy*dy+dz*dz),1);
      // bonsaidt.Fill(bslike->get_zero()-offsetT-mct[i],1);
      // bonsaix.Fill(10*bsfit->xfit(),1);
      // bonsaiy.Fill(10*bsfit->yfit(),1);
      // bonsaiz.Fill(10*bsfit->zfit(),1);

      // dx=10*bsfit->xfit();
      // dy=10*bsfit->yfit();
      //
      // bonsair2.Fill(dx*dx+dy*dy,1);
      // bonsait.Fill(bslike->get_zero()-offsetT,1);

      *bonsai_vtxfit=bsfit->xfit();
      bonsai_vtxfit[1]=bsfit->yfit();
      bonsai_vtxfit[2]=bsfit->zfit();
      n9 =  bslike->nwind(bonsai_vtxfit,-3,6);
      bslike->tgood(bonsai_vtxfit,0,goodn[0]);

      delete(bsgrid);
      delete(bsgdn);

      bslike->set_hits(NULL);

      temp = prim->GetMomentum();
      temp = temp.Unit();
      mcdx[i] = temp.X();
      mcdy[i] = temp.Y();
      mcdz[i] = temp.Z();
      mcU = temp.X();mcV = temp.Y();mcW = temp.Z();

      totNHIT = nhit;
      dxx = x-prev_x;dyy = y-prev_y;dzz = z-prev_z;

      if(dxx>1e6)
      {
        dxx = 0.;dyy = 0.;dzz = 0.;
      }
      dxmcx = x-mcX;dymcy = y-mcY;dzmcz = z-mcZ;
      dt1 = double(timestamp_s)+double(timestamp_ns)/1e9-old_t;
      // printf("%f %f %f %f %f\n",double(timestamp_s),double(timestamp_ns),dt1,old_t,double(timestamp_s)+double(timestamp_ns)/1e9);
      dt0 = bslike->get_zero()-offsetT;
      prev_x=x;prev_y=y;prev_z=z;
      old_t = double(timestamp_s)+double(timestamp_ns)/1e9;
      _goodness = goodn[0];
      _dirGoodness = goodn[1];

      data->Fill();
    }

  }
  out->cd();
  data->Write();

  out->Close();
  delete(bsfit);
  delete(bslike);
  delete(bsgeom);
  return 0;
}
