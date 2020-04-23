/* SplitEVDAQ is an extension of the SimpleDAQ that converts hits into multiple
 * triggers, and places those in new events (not subevents) to better simulate
 * data and produce combined datasets.
*/
#include <vector>
#include <algorithm>
#include <RAT/SplitEVDAQProc.hh>
#include <RAT/DB.hh>
#include <G4ThreeVector.hh>
#include <RAT/DetectorConstruction.hh>

using namespace std;

namespace RAT {

SplitEVDAQProc::SplitEVDAQProc() : Processor("splitevdaq") {
  ldaq = DB::Get()->GetLink("SplitEVDAQ");
  fEventCounter = 0;
}

Processor::Result SplitEVDAQProc::DSEvent(DS::Root *ds) {
  // This DAQ will convert hits on PMTs through time into trigger pulses
  // which can fire a global event trigger. Each trigger will correspond
  // to a single sub-event in the datastructure. 
  const double pulseWidth        = ldaq->GetD("pulse_width");
  const double triggerThreshold  = ldaq->GetD("trigger_threshold");
  const double triggerWindow     = ldaq->GetD("trigger_window");
  const double pmtLockout        = ldaq->GetD("pmt_lockout");
  const double triggerLockout    = ldaq->GetD("trigger_lockout");
  const double triggerResolution = ldaq->GetD("trigger_resolution");
  const double lookback          = ldaq->GetD("lookback");
  // Not included yet
  // - Noise on the trigger pulse height, rise-time, etc
  // - Disciminator on charge (all hits assumed to trigger)

  DS::MC *mc = ds->GetMC();
  // Prune the previous EV branchs if one exists
  if( ds->ExistEV() ) ds->PruneEV();

  // First loop through the PMTs and create a summed trigger
  vector<double> trigPulses;
  for (int imcpmt=0; imcpmt < mc->GetMCPMTCount(); imcpmt++)
  {
    DS::MCPMT *mcpmt = mc->GetMCPMT(imcpmt);
    double lastTrigger = -100000.0;
    for(int pidx=0; pidx < mcpmt->GetMCPhotonCount(); pidx++)
    {
      DS::MCPhoton* photon = mcpmt->GetMCPhoton(pidx);
      double time = photon->GetFrontEndTime();
      if (time > (lastTrigger + pmtLockout))
      {
        trigPulses.push_back(time);
        lastTrigger = time;
      }
    }
  }
  if( trigPulses.size() < 1 ) return Processor::OK; // We're done, no triggers

  double start = *std::min_element(trigPulses.begin(), trigPulses.end());
  start = floor(start / triggerResolution) * triggerResolution;
  double end = *std::max_element(trigPulses.begin(), trigPulses.end());
  end = (floor(end / triggerResolution)+1) * triggerResolution;
  std::sort(trigPulses.begin(), trigPulses.end());

  // Turns hits into a histogram of trigger pulse leading edges
  //        _
  //   _   | |    _
  // _| |__| |___| |___
  int nbins = floor( (end - start) / triggerResolution ) ;
  double bw = (end-start)/nbins;
  vector<double> triggerTrain( nbins );
  for( auto v : trigPulses )
  {
    int select = int( (v - start) / bw );
    triggerTrain[select] += 1.0;
  }

  // Spread each bin out to the trigger pulse width to pass to a discriminator
  //             | 
  //.............|_____ .... trigger threshold .....
  //        _____|     |____
  //       |     |          |____
  //   ____|     |               |____
  // _|          | global trigger!    |___
  vector<double> triggerHistogram( nbins );
  for(int i=0; i<nbins; i++)
  {
    double x = triggerTrain[i];
    if( x > 0 )
    {
      for( int j=i; j<i+pulseWidth; j++ )
      {
        if( j >= nbins )
          break;
        triggerHistogram[j] += x;
      }
    }
  }

  // Trigger the detector based on triggerThreshold
  double lastTrigger = -100000.0;
  vector<double> triggerTimes;
  for(int i=0; i<nbins; i++)
  {
    double v = triggerHistogram[i];
    if( v >= triggerThreshold ) // check for trigger
    {
      if( (i*bw)+start > (lastTrigger + triggerWindow + triggerLockout) )
      {
        lastTrigger = (i*bw)+start;
        triggerTimes.push_back(lastTrigger);
      }
    }
  }

  // Place the correct hits, charges, etc into the right trigger windows
  for( auto tt : triggerTimes )
  {
    DS::EV *ev = ds->AddNewEV();
    ev->SetID(fEventCounter++);
    ev->SetCalibratedTriggerTime( tt );
    double totalEVCharge = 0; // What does total charge get used for?
    for( int imcpmt=0; imcpmt < mc->GetMCPMTCount(); imcpmt++)
    {
      DS::MCPMT *mcpmt = mc->GetMCPMT(imcpmt);
      int pmtID = mcpmt->GetID();
      // Check if the mcpmt has a time within one pulsewidth of the trigger window
      bool pmtInEvent = false;
      double integratedCharge = 0;
      vector<double> hitTimes;
      if( mcpmt->GetMCPhotonCount() > 0 )
      {
        for(int pidx=0; pidx < mcpmt->GetMCPhotonCount(); pidx++)
        {
          DS::MCPhoton* photon = mcpmt->GetMCPhoton(pidx);
          double time = photon->GetFrontEndTime();
          if ( ( time > (tt - lookback) ) && ( time < (tt + triggerWindow) ) )
          {
            pmtInEvent = true;
            hitTimes.push_back(time);
            integratedCharge += mcpmt->GetCharge();
          }
        }
      }
      if( pmtInEvent )
      {
        DS::PMT* pmt = ev->AddNewPMT();
        pmt->SetID(pmtID);
        pmt->SetTime( *std::min_element( hitTimes.begin(), hitTimes.end() ) );
        pmt->SetCharge( integratedCharge );
        totalEVCharge += integratedCharge;
      }
    } // Done looping over PMTs
    ev->SetTotalCharge( totalEVCharge );
  }
  
  return Processor::OK;
}

} // namespace RAT

