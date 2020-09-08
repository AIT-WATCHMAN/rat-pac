#ifndef __RAT_PMTMatching__
#define __RAT_PMTMatching__

#include <TObject.h>
#include <RAT/DS/MC.hh>
#include <RAT/DS/PMT.hh>
#include <RAT/DS/MCPMT.hh>
#include <RAT/DS/MCPhoton.hh>

namespace RAT{

  /*
   * Match between trigger PMT and MCPMT/MCPhoton objects
  */

  // Returns all MCPMTs with matching IDs
  std::vector<DS::MCPMT*> MCPMTsFromPMT(DS::PMT& pmt, DS::MC& mc);

  // Returns all MCPhotons that contributed to PMT hit
  std::vector<DS::MCPhoton*> MCPhotonsFromPMT(DS::PMT& pmt, DS::MC& mc);

  // Returns key with maximum value in map
  std::string MaxProcess(std::map<std::string, double> processMap);

  // Returns the photon production process that contributed the most energy to the PMT hit
  std::string ProcessFromEnergy(DS::PMT& pmt, DS::MC& mc, bool rollupScint=true);
  std::string ProcessFromEnergy(DS::MCPMT& pmt, bool rollupScint=true);

  // Returns the photon production process that contributed the most photons to the PMT hit
  std::string ProcessFromNHit(DS::PMT& pmt, DS::MC& mc, bool rollupScint=true);
  std::string ProcessFromNHit(DS::MCPMT& pmt, bool rollupScint=true);

}

#endif
