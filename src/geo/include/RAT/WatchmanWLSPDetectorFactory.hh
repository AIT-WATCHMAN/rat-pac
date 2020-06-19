#ifndef __RAT_WatchmanWLSPDetectorFactory__
#define __RAT_WatchmanWLSPDetectorFactory__

#include <RAT/DetectorFactory.hh>

namespace RAT {

class WatchmanWLSPDetectorFactory : public DetectorFactory {

    public:
        WatchmanWLSPDetectorFactory() { }
        virtual ~WatchmanWLSPDetectorFactory() { }
        
    protected:
        virtual void DefineDetector(DBLinkPtr detector);

};

} //namespace RAT

#endif
