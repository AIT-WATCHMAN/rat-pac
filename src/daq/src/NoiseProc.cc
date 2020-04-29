#include <vector>
#include <map>
#include <Randomize.hh>
#include <RAT/NoiseProc.hh>
#include <RAT/DB.hh>
#include <RAT/DS/RunStore.hh>
#include <RAT/DetectorConstruction.hh>
#include <RAT/Log.hh>

using namespace std;

namespace RAT {

NoiseProc::NoiseProc() : Processor("noise") {
  DBLinkPtr lnoise = DB::Get()->GetLink("NOISEPROC");

  fNoiseRate   = lnoise->GetD("noise_rate");
  fLookback    = lnoise->GetD("noise_lookback");
  fLookforward = lnoise->GetD("noise_lookforward");
  fMaxTime     = lnoise->GetD("noise_maxtime");
}

Processor::Result NoiseProc::DSEvent(DS::Root* ds) {
  // Noise moved to a processor from GSim, this is a special
  // case of a processor modifying the MC branch

  // Run Information
  DS::Run* run         = DS::RunStore::Get()->GetRun(ds);
  DS::PMTInfo* pmtinfo = run->GetPMTInfo();

  // Write over MC
  DS::MC* mc = ds->GetMC();
  PruneNoise(mc);
  // Loop through current hits to get a full window and hit pmts
  double firsthittime = std::numeric_limits<double>::max();
  double lasthittime  = std::numeric_limits<double>::min();

  // <pmtid, mcpmtlocation>
  std::map<int, int> mcpmtObjects;

  for(int imcpmt=0; imcpmt < mc->GetMCPMTCount(); imcpmt++)
  {
    DS::MCPMT* mcpmt = mc->GetMCPMT(imcpmt);
    mcpmtObjects[mcpmt->GetID()] = imcpmt;
    for(int pidx=0; pidx < mcpmt->GetMCPhotonCount(); pidx++)
    {
      DS::MCPhoton* photon = mcpmt->GetMCPhoton(pidx);
      double hittime = photon->GetHitTime();
      if( hittime < firsthittime ) firsthittime = hittime;
      if( hittime > lasthittime  ) lasthittime  = hittime;
    }
  }
  // Cap how far forward to look in cast of weird geant-4 lifetimes
  if( lasthittime > fMaxTime ) lasthittime = fMaxTime;
  // And really just in case
  if( firsthittime < -fMaxTime ) firsthittime = -fMaxTime;
  
  double noiseBegin       = firsthittime - fLookback;
  double noiseEnd         = lasthittime + fLookforward;
  double noiseWindowWidth = noiseEnd - noiseBegin;
  size_t pmtCount         = pmtinfo->GetPMTCount();
  double darkCount        = fNoiseRate * noiseWindowWidth * pmtCount * 1e-9;

  int noiseHits = static_cast<int>(floor(CLHEP::RandPoisson::shoot(darkCount)));
  for(int ihit=0; ihit < noiseHits; ihit++)
  {
    int pmtid = static_cast<int>(G4UniformRand() * pmtCount);
    if( !mcpmtObjects.count(pmtid) )
    {
      DS::MCPMT* mcpmt = mc->AddNewMCPMT();
      mcpmtObjects[pmtid] = mc->GetMCPMTCount() - 1;
      mcpmt->SetID(pmtid);
      mcpmt->SetType( pmtinfo->GetType(pmtid) );
    }
    DS::MCPMT* mcpmt = mc->GetMCPMT( mcpmtObjects[pmtid] );
    double hittime = noiseBegin + G4UniformRand()*noiseWindowWidth;
    AddNoiseHit( mcpmt, hittime );
  }

  return Processor::OK;
}

void NoiseProc::PruneNoise(DS::MC* mc)
{
  // Remove hits already flagged as noise hits so we do not double count.
  return;
}

void NoiseProc::AddNoiseHit( DS::MCPMT* mcpmt, double hittime )
{
    DS::MCPhoton* photon = mcpmt->AddNewMCPhoton();
    photon->SetDarkHit(true);
    photon->SetLambda(0.0);
    photon->SetPosition(TVector3(0, 0, 0));
    photon->SetMomentum(TVector3(0, 0, 0));
    photon->SetPolarization(TVector3(0, 0, 0));
    photon->SetTrackID(-1);
    photon->SetHitTime( hittime );
    // Modify these to check the pmt time and charge model
    photon->SetFrontEndTime( hittime );
    photon->SetCharge( 1 );
    return;
}

void NoiseProc::SetD(std::string param, double value)
{
  if (param == "rate")
    if(value > 0)
      fNoiseRate = value;
    else
      throw ParamInvalid(param, "Noise rate must be positive");
  else
    throw ParamUnknown(param);
}

} // namespace RAT
