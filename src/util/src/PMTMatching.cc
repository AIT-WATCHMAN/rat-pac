#include <RAT/PMTMatching.hh>
#include <iostream>

namespace RAT{


  // Returns all MCPMTs with matching IDs
  std::vector<DS::MCPMT*> MCPMTsFromPMT(DS::PMT* pmt, DS::MC* mc) {
    int id = pmt->GetID();
    std::vector<DS::MCPMT*> matchedPmts;

    for(int i = 0; i < mc->GetMCPMTCount(); i++){
      int mcId = mc->GetMCPMT(i)->GetID();
      if(id != mcId) continue;
      matchedPmts.push_back(mc->GetMCPMT(i));
    }

    return matchedPmts;
  }


  // Returns all MCPhotons that contributed to PMT hit
  std::vector<DS::MCPhoton*> MCPhotonsFromPMT(DS::PMT* pmt, DS::EV* trig, DS::MC* mc){
    int id = pmt->GetID();
    // Get the global time of the PMT hit
    double time = pmt->GetTime() + trig->GetCalibratedTriggerTime();
    std::vector<DS::MCPhoton*> matchedPhotons;

    for(int i = 0; i < mc->GetMCPMTCount(); i++){
      int mcId = mc->GetMCPMT(i)->GetID();
      // Find MCPMTs with the same ID
      if(id != mcId) continue;
      if(mc->GetMCPMT(i)->GetMCPhotonCount() == 0) continue;
      for(int j = 0; j < mc->GetMCPMT(i)->GetMCPhotonCount(); j++){
        // Return MCPhotons within trigger window
        // TODO this is using the LessSimpleDAQ trigger window, would be good to have a way to set this from the event
        double mcTime = mc->GetMCPMT(i)->GetMCPhoton(j)->GetFrontEndTime();
        if(std::abs(time - mcTime) > 800) continue;
        matchedPhotons.push_back(mc->GetMCPMT(i)->GetMCPhoton(j));
      }
    }

    return matchedPhotons;
  }

  std::vector<DS::MCPhoton*> MCPhotonsFromPMT(DS::PMT* pmt, DS::Root* event){
    // Get the MC and trigger info by matching the PMTs
    DS::MC* mc = event->GetMC();
    for(int i = 0; i < event->GetEVCount(); i++){
      DS::EV* trig = event->GetEV(i);
      for(int j = 0; j < trig->GetPMTCount(); j++){
        if(trig->GetPMT(j)->GetID() == pmt->GetID() && trig->GetPMT(j)->GetTime() == pmt->GetTime()){
          return MCPhotonsFromPMT(pmt, trig, mc);
        }
      }
    }

    // If no matching PMTs found return an empty vector
    std::vector<DS::MCPhoton*> empty;
    return empty;
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
  std::string ProcessFromEnergy(DS::PMT* pmt, DS::EV* trig, DS::MC* mc, bool rollupScint){
    std::vector<DS::MCPhoton*> mcphotons = MCPhotonsFromPMT(pmt, trig, mc);
    return ProcessFrom(mcphotons, "energy", rollupScint);
  }

  std::string ProcessFromEnergy(DS::PMT* pmt, DS::Root* event, bool rollupScint){
    std::vector<DS::MCPhoton*> mcphotons = MCPhotonsFromPMT(pmt, event);
    return ProcessFrom(mcphotons, "energy", rollupScint);
  }

  std::string ProcessFromEnergy(DS::MCPMT* pmt, bool rollupScint){
    std::map<std::string, double> processEdepMap;
    for(int i = 0; i < pmt->GetMCPhotonCount(); i++){
      if(rollupScint && pmt->GetMCPhoton(i)->GetProcess()=="Reemission"){
        processEdepMap["Scintillation"] += pmt->GetMCPhoton(i)->GetCharge();
      }
      else{
        processEdepMap[pmt->GetMCPhoton(i)->GetProcess()] += pmt->GetMCPhoton(i)->GetCharge();
      }
    }
    return MaxProcess(processEdepMap);
  }


  // Returns the photon production process that contributed the most photons to the PMT hit
  std::string ProcessFromNHit(DS::PMT* pmt, DS::EV* trig, DS::MC* mc, bool rollupScint){
    std::vector<DS::MCPhoton*> mcphotons = MCPhotonsFromPMT(pmt, trig, mc);
    return ProcessFrom(mcphotons, "hits", rollupScint);
  }

  std::string ProcessFromNHit(DS::PMT* pmt, DS::Root* event, bool rollupScint){
    std::vector<DS::MCPhoton*> mcphotons = MCPhotonsFromPMT(pmt, event);
    return ProcessFrom(mcphotons, "hits", rollupScint);
  }

  std::string ProcessFromNHit(DS::MCPMT* pmt, bool rollupScint){
   std::map<std::string, double> processHitMap;
   for(int i = 0; i < pmt->GetMCPhotonCount(); i++){
      if(rollupScint && pmt->GetMCPhoton(i)->GetProcess()=="Reemission"){
        processHitMap["Scintillation"] += 1;
      }
      else{
        processHitMap[pmt->GetMCPhoton(i)->GetProcess()] += 1;
      }
    }
    return MaxProcess(processHitMap); 
  }

  
  // Returns the photon production process that contributed the most of a certain metric (energy or hits) to a PMT hit
  std::string ProcessFrom(std::vector<DS::MCPhoton*> mcphotons, std::string metric, bool rollupScint){
    if(mcphotons.size() == 0) return "unknown";
    std::map<std::string, double> processEdepMap;
    for(auto& mcphoton : mcphotons){
      double value = 1;
      if(metric == "energy"){
        value = mcphoton->GetCharge();
      }
      if(rollupScint && mcphoton->GetProcess()=="Reemission"){
        processEdepMap["Scintillation"] += value;
      }
      else{
        processEdepMap[mcphoton->GetProcess()] += value;
      }
    }
    return MaxProcess(processEdepMap);
  }

}
