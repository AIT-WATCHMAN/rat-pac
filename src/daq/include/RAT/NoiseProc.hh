#ifndef __RAT_NoiseProc__
#define __RAT_NoiseProc__

#include <RAT/Processor.hh>

namespace RAT {


class NoiseProc : public Processor {
public:
  NoiseProc();
  virtual ~NoiseProc() { };
  virtual Processor::Result DSEvent(DS::Root *ds);

  void PruneNoise(DS::MC*);
  void AddNoiseHit(DS::MCPMT*, double); 
  void SetD(std::string, double);

protected:
  double fNoiseRate;
  double fLookback;
  double fLookforward;
  double fMaxTime;
};


} // namespace RAT

#endif
