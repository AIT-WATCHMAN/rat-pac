#ifndef __RAT_PMTMatching__
#define __RAT_PMTMatching__

#include <TObject.h>
#include <RAT/DS/Root.hh>
#include <RAT/DS/MC.hh>
#include <RAT/DS/EV.hh>
#include <RAT/DS/PMT.hh>
#include <RAT/DS/MCPMT.hh>
#include <RAT/DS/MCPhoton.hh>

namespace RAT{

  /*
   * Helper functions for matching between triggered PMT hits and 
   * MCPMT/MCPhoton objects, and matching PMT/MCPMT hits to the
   * dominant photon production process by either total energy or
   * total number of photons.
   * Can be used in ROOT macro:
   * > for(int i = 0; i < event->GetMC()->GetMCPMTCount(); i++){
   * >  RAT::DS* mcpmt = event->GetMC()->GetMCPMT(i);
   * >  std::string process = RAT::ProcessFromEnergy(mcpmt);
   * > }
  */

  // Returns all MCPMTs with matching IDs
  std::vector<DS::MCPMT*> MCPMTsFromPMT(DS::PMT* pmt, DS::MC* mc);

  // Returns all MCPhotons that contributed to PMT hit
  std::vector<DS::MCPhoton*> MCPhotonsFromPMT(DS::PMT* pmt, DS::EV* trig, DS::MC* mc);
  std::vector<DS::MCPhoton*> MCPhotonsFromPMT(DS::PMT* pmt, DS::Root* event);

  // Returns key with maximum value in map
  std::string MaxProcess(std::map<std::string, double> processMap);

  // Returns the photon production process that contributed the most energy to the PMT hit
  std::string ProcessFromEnergy(DS::PMT* pmt, DS::EV* trig, DS::MC* mc, bool rollupScint=true);
  std::string ProcessFromEnergy(DS::PMT* pmt, DS::Root* event, bool rollupScint=true);
  std::string ProcessFromEnergy(DS::MCPMT* pmt, bool rollupScint=true);

  // Returns the photon production process that contributed the most photons to the PMT hit
  std::string ProcessFromNHit(DS::PMT* pmt, DS::EV* trig, DS::MC* mc, bool rollupScint=true);
  std::string ProcessFromNHit(DS::PMT* pmt, DS::Root* event, bool rollupScint=true);
  std::string ProcessFromNHit(DS::MCPMT* pmt, bool rollupScint=true);

  // Returns the photon production process that contributed the most of a certain metric (energy or hits) to a PMT hit
  std::string ProcessFrom(std::vector<DS::MCPhoton*> mcphotons, std::string metric, bool rollupScint=true);

}

#endif
