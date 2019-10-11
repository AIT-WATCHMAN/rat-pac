{
// First go at an event display. User must run visualiser on root file first. User must replace name of output file.

TFile *_file0 = TFile::Open("tomi_daq.root");

TTree *runSummary = _file0->Get("runSummary");
runSummary->SetMarkerColor(0);

TTree *data = _file0->Get("data");

TTree *red  = data.Clone();
red.SetMarkerStyle(20);
red.SetMarkerSize(0.6);
red.SetMarkerColor(kRed);

TTree *green  = data.Clone();
green.SetMarkerStyle(20);
green.SetMarkerSize(0.5);
green.SetMarkerColor(kOrange);

TTree *blue  = data.Clone();
blue.SetMarkerStyle(20);
blue.SetMarkerSize(0.5);
blue.SetMarkerColor(kGreen);

TCanvas *c1 = new TCanvas("c1","c1",1200,1000);
c1->cd(1);
gPad->SetFillColor(1);
gPad->SetFrameFillColor(1);
gStyle->SetOptTitle(0);
Int_t _r, _g,_b;
for(Int_t i = 1; i < data->GetEntries();i++){

 runSummary->Draw("v_pmt_ref:u_pmt_ref","","");
 _r = red->Draw("v_pmt:u_pmt",Form("t_pmt<20 && Entry$==%d",i),"same");
 _g = green->Draw("v_pmt:u_pmt",Form("t_pmt>20 && t_pmt <40  && Entry$==%d",i),"same");
 _b = blue->Draw("v_pmt:u_pmt",Form("t_pmt>40 && Entry$==%d",i),"same");
 if (_r>0 || _g>0 || _b >0){
  c1->SaveAs(Form("event%d_t.gif",i));
 }
 
  runSummary->Draw("v_pmt_ref:u_pmt_ref","","");
 _r = red->Draw("v_pmt:u_pmt",Form("q_pmt>30 && Entry$==%d",i),"same");
 _g = green->Draw("v_pmt:u_pmt",Form("q_pmt>15 && q_pmt <30  && Entry$==%d",i),"same");
 _b = blue->Draw("v_pmt:u_pmt",Form("q_pmt<15 && Entry$==%d",i),"same");
 if (_r>0 || _g>0 || _b >0){
  c1->SaveAs(Form("event%d_q.gif",i));
 }
}

}
