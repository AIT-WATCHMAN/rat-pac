#include <RAT/PMTMatching.hh>

namespace RAT{

  // Returns all MCPMTs with matching IDs
  std::vector<DS::MCPMT*> MCPMTsFromPMT(DS::PMT& pmt, DS::MC& mc) {
    int id = pmt.GetID();
    double time = pmt.GetTime();
    std::vector<DS::MCPMT*> matchedPmts;
    for(int i = 0; i < mc.GetMCPMTCount(); i++){
      int mcId = mc.GetMCPMT(i)->GetID();
      if(id != mcId) continue;
      matchedPmts.push_back(mc.GetMCPMT(i));
    }
    return matchedPmts;
  }

  // Returns all MCPhotons that contributed to PMT hit
  std::vector<DS::MCPhoton*> MCPhotonsFromPMT(DS::PMT& pmt, DS::MC& mc){
    int id = pmt.GetID();
    double time = pmt.GetTime();
    std::vector<DS::MCPhoton*> matchedPhotons;
    for(int i = 0; i < mc.GetMCPMTCount(); i++){
      int mcId = mc.GetMCPMT(i)->GetID();
      if(id != mcId) continue;
      if(mc.GetMCPMT(i)->GetMCPhotonCount() == 0) continue;
      for(int j = 0; j < mc.GetMCPMT(i)->GetMCPhotonCount(); j++){
        double mcTime = mc.GetMCPMT(i)->GetMCPhoton(j)->GetFrontEndTime();
        if(std::abs(time - mcTime) > 800) continue;
        matchedPhotons.push_back(mc.GetMCPMT(i)->GetMCPhoton(j));
      }
    }
    return matchedPhotons;
  }

  // Returns key with maximum value in map
  std::string MaxProcess(std::map<std::string, double> processMap){
    double max = 0;
    std::string maxProcess = "unknown";
    for(auto const& kv : processMap){
      if(kv.second > max){
        max = kv.second;
        maxProcess = kv.first;
      }
    }
    return maxProcess;
  }

  // Returns the photon production process that contributed the most energy to the PMT hit
  std::string ProcessFromEnergy(DS::PMT& pmt, DS::MC& mc){
    std::vector<DS::MCPhoton*> mcphotons = MCPhotonsFromPMT(pmt, mc);
    if(mcphotons.size() == 0) return "unknown";
    std::map<std::string, double> processEdepMap;
    for(auto& mcphoton : mcphotons){
      processEdepMap[mcphoton->GetProcess()] += mcphoton->GetCharge();
    }
    return MaxProcess(processEdepMap);
  }

  std::string ProcessFromEnergy(DS::MCPMT& pmt){
    std::map<std::string, double> processEdepMap;
    for(int i = 0; i < pmt.GetMCPhotonCount(); i++){
      processEdepMap[pmt.GetMCPhoton(i)->GetProcess()] += pmt.GetMCPhoton(i)->GetCharge();
    }
    return MaxProcess(processEdepMap);
  }

  // Returns the photon production process that contributed the most photons to the PMT hit
  std::string ProcessFromNHit(DS::PMT& pmt, DS::MC& mc){
    std::vector<DS::MCPhoton*> mcphotons = MCPhotonsFromPMT(pmt, mc);
    if(mcphotons.size() == 0) return "unknown";
    std::map<std::string, double> processHitMap;
    for(auto& mcphoton : mcphotons){
      processHitMap[mcphoton->GetProcess()] += 1;
    }
    return MaxProcess(processHitMap);
  }

  std::string ProcessFromNHit(DS::MCPMT& pmt){
   std::map<std::string, double> processHitMap;
   for(int i = 0; i < pmt.GetMCPhotonCount(); i++){
      processHitMap[pmt.GetMCPhoton(i)->GetProcess()] += 1;
    }
    return MaxProcess(processHitMap); 
  }

}
