#ifndef __RAT_LetterboxFactory__
#define __RAT_LetterboxFactory__

#include <RAT/DetectorFactory.hh>

namespace RAT {

class LetterboxFactory : public DetectorFactory {

    public:
        LetterboxFactory() { }
        virtual ~LetterboxFactory() { }
        
    protected:
        virtual void DefineDetector(DBLinkPtr detector);

};

} //namespace RAT

#endif
