#include <RAT/IBDgenMessenger.hh>
#include <RAT/IBDgen.hh>

#include <G4UIcommand.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4UIcmdWithAString.hh>
#include <G4String.hh>

namespace RAT {
  IBDgenMessenger::IBDgenMessenger(IBDgen* re) :
    ibdgen(re)
  {
    // Commands will be called in the mac with /generator/ibd/
    G4UIdirectory* dir = new G4UIdirectory("/generator/ibd/");
    dir->SetGuidance("Control the IBD neutrino spectrum of the IBD generator");

    SpectrumUseCmd = new G4UIcmdWithAString("/generator/ibd/spectrum", this);
    SpectrumUseCmd->SetGuidance("Set the spectrum (index of the IBD ratdb table)");
    SpectrumUseCmd->SetParameterName("Spectrum", false);
    SpectrumUseCmd->SetDefaultValue( "default" );
  }

  IBDgenMessenger::~IBDgenMessenger() 
  {
    delete SpectrumUseCmd;
  }

  void IBDgenMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
  {
    if ( command == SpectrumUseCmd )
    {
      ibdgen->SetSpectrumIndex( newValue );
    }
    else
    {
      G4cerr << "Error: Invalid IBDgenMessenger \"set\" command" << G4endl;
    }
  }

  G4String IBDgenMessenger::GetCurrentValue(G4UIcommand* command)
  {
    if ( command == SpectrumUseCmd )
    {
      return ibdgen->GetSpectrumIndex();
    }
    //Get here, you return an error.
    return G4String("Error: Invalid IBDgenMessenger \"get\" command");
  }

}  //namespace RAT
