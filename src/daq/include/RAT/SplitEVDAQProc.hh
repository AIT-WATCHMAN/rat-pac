#ifndef __RAT_SplitEVDAQProc__
#define __RAT_SplitEVDAQProc__

#include <RAT/Processor.hh>
#include <RAT/DB.hh>

namespace RAT {


class SplitEVDAQProc : public Processor {
public:
  SplitEVDAQProc();
  virtual ~SplitEVDAQProc() { };
  virtual Processor::Result DSEvent(DS::Root *ds);

protected:
  int fEventCounter;
  std::vector<double> fSPECharge;
  DBLinkPtr ldaq;
};


} // namespace RAT

#endif
