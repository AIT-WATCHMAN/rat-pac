// Generates an neutrino-elastic scattering event, based on the
// cross-section as function of neutrino energy and the electron's
// recoil energy.  Allow for variations in the weak mixing angle and
// the possibility of a neutrino magnetic moment
//
// J. Formaggio (UW) -02/09/2005

// Converted to Geant4+GLG4Sim+RAT by Bill Seligman (07-Feb-2006).
// I'm following the code structure of the IBD classes:
// RATVertexGen_ES handles the G4-related tasks of constructing an
// event, while this class deals with the physics of the
// cross-section.  Some of the code (the flux in particular) is copied
// from IBDgen.
 
// Changed to read in Boulby spectrum by default and to allow 
// user to set spectrum from macro via /generator/es/spec specname
// Liz Kneale (Feb 2020)

#include <RAT/ESgen.hh>
#include <RAT/ESgenMessenger.hh>
#include <RAT/DB.hh>

#include <G4ParticleDefinition.hh>
#include <G4ParticleTable.hh>
#include <G4ThreeVector.hh>
#include <Randomize.hh>
#include <CLHEP/Units/PhysicalConstants.h>
#include <CLHEP/Units/SystemOfUnits.h>

#include <cmath>
#define G4std  std

namespace RAT {

  // WGS: Constants copied from various places to make the code work.
  const double XMaxDefault  = 1e-45; // Reasonable minimum for x-section (cm^2).
  const double GFERMI = 1.16639e-11 / CLHEP::MeV / CLHEP::MeV;
  const double XcMeVtoCmsqrd = 0.389379292e-21;

  // WGS: We have to start from some value of sin2theta; use the stanard-model value:
  const double ESgen::WEAKANGLE = 0.2227;
  const int    ESgen::NTRIAL    = 10000;
  const std::string ESgen::SPEC = "boulby";

  ESgen::ESgen()
  {
    // Initialize everything.
    Reset();
    // Create a messenger to allow the user to change some ES parameters.
    messenger = new ESgenMessenger(this);

    // Initialise the spectrum.
    G4String spec = "boulby";
    DBLinkPtr _lspec    = DB::Get()->GetLink("SPECTRUM", spec);  // default to Boulby spectrum
    std::vector<double> spec_E = _lspec->GetDArray("spec_e");
    Emin = 0.;
    Emax = 0.;
    // Flux function
    rmpflux.Set(_lspec->GetDArray("spec_e"), _lspec->GetDArray("spec_mag"));
    // Other useful numbers
    FluxMax = 0.;
    // Get the electron mass.
    G4ParticleDefinition* electron = G4ParticleTable::GetParticleTable()->FindParticle("e-");  
    massElectron = electron->GetPDGMass();
  }


  ESgen::~ESgen()
  {
    // I compulsively delete unused pointers.
    if ( messenger != 0 )
      {
	delete messenger;
	messenger = 0;
      }
  }


  CLHEP::HepLorentzVector ESgen::GenerateEvent(const G4ThreeVector& theNeutrino)
  {
    // Get the spectrum from user input; defaults to boulby.
    G4String spec = GetSpectrum();
    DBLinkPtr _lspec    = DB::Get()->GetLink("SPECTRUM", spec);  // default to Boulby spectrum
    // Get parameters from database.
    // Read in the energy values from the spectrum.
    std::vector<double> spec_E = _lspec->GetDArray("spec_e");
    Emin = spec_E.front();
    Emax = spec_E.back();

    // Create the flux function from the spectrum.
    rmpflux.Set(_lspec->GetDArray("spec_e"), _lspec->GetDArray("spec_mag"));
    // Find the maximum flux from the spectrum.
    std::vector<double> spec_F = _lspec->GetDArray("spec_mag");
    FluxMax = *max_element(spec_F.begin(),spec_F.end());
    //
    //  Check if the maximum throwing number has been set.
    //
    if (!GetNormFlag()) SetXSecMax(NTRIAL);
    double XSecNorm = GetXSecMax();
  
    // Throw values against a cross-section.
    bool passed=false;
    double E, Nu;

    while(!passed){
      // Pick a random E in the spectral energy range and Nu.
      E = GetRandomNumber(Emin, Emax);
      // Pick a randon Nu energy between 0 and the electron energy.
      Nu = GetRandomNumber(0., E);
      
      // Decided whether to draw again based on relative cross-section.
      // Check that the 
      float XCtest = XSecNorm * FluxMax * GetRandomNumber(0.,1.);
      double XCWeight = GetXSec(E, Nu);
      double FluxWeight = rmpflux(E);
      passed = XCWeight * FluxWeight > XCtest;
    }

    //
    //  Calculate the neutrino pT and incoming angle
    //
    G4double pT = E * theNeutrino.perp()/theNeutrino.mag();
    G4double pTq = asin(pT/E);

    //
    //  Set kinematic variables from kinetic energy
    //
    G4double X = 1.;
    G4double Y = Nu / E;
    G4double Q2  = 2. * E * X * Y * massElectron;
    G4double sin2q = Q2 / (4. * E * (E - Nu));
    G4double theta_lab = 2. * asin(sqrt(sin2q)) + pTq;
    G4double phi = GetRandomNumber(0., 2.*M_PI);

    //
    //  Now that energy/Q2 is selected, write a momentum transfer 4-vector q.
    //
    G4double qp = sqrt(pow(Nu,2) + Q2);
    CLHEP::HepLorentzVector qVector;
    qVector.setPx(qp * sin(theta_lab) * cos(phi));
    qVector.setPy(qp * sin(theta_lab) * sin(phi));
    qVector.setPz(qp * cos(theta_lab));
    qVector.setE(Nu);

    //
    // Let pe_new = pe - (pv - pv_new) == pe - q;
    //
    CLHEP::HepLorentzVector theElectron;
    theElectron.setE(massElectron);
    theElectron += qVector;

    return theElectron;
  }

  void ESgen::Reset()
  {
    XSecMax = 0.0;
    SetNormFlag(false);
    SetMixingAngle(WEAKANGLE);
    SetNeutrinoMoment(0.0);
    SetSpectrum(SPEC);
  }

  void ESgen::Show()
  {
    G4cout << "Elastic Scatteing Settings:" << G4endl;
    G4cout << "Weak Mixing Angle (sinsq(ThetaW)):" << GetMixingAngle() << G4endl;
    G4cout << "Neutrino Magnetic Moment: " << GetMagneticMoment() << G4endl;
    G4cout << "Spectrum: " << GetSpectrum() << G4endl;
  }


  void ESgen::SetSpectrum(G4String spec)
  {
    Spectrum = spec;
  }

  G4String ESgen::GetSpectrum()
  {
    return Spectrum;
  } 


  void ESgen::SetMixingAngle(double sin2thw)
  {
    if ((sin2thw < 0.) || (sin2thw > 1.)) 
      {
	G4cerr << "Error in value setting." << G4endl;
	return;
      }
    SinSqThetaW = sin2thw;
  }

  void ESgen::SetNeutrinoMoment(double vMu)
  {
    if (vMu < 0.) 
      {
	G4cerr << "Error in value setting." << G4endl;
	return;
      }
    MagneticMoment = vMu;
  }
  
  double ESgen::GetXSec(double Enu, double T){

    double XC = 0.;

    //  Set up constants for cross-section scale.  
    double XCunits = XcMeVtoCmsqrd;
    double Sigma0 = GFERMI * GFERMI * massElectron / (2. * M_PI);

    //  Set up weak mixing parameters & neutrino magnetic moment.
    double sin2thw = GetMixingAngle();
    double vMu = GetMagneticMoment();
    double g_v = 2.*sin2thw + 0.5;
    double g_a = -0.5;

    //  Reject events in prohibited regions.
    if (T > Enu) return 0.;

    //  Compute differential cross-section
    XC = pow((g_v + g_a),2)
      +pow((g_v - g_a),2)*pow((1.-T/Enu),2)
      +(pow(g_a,2) - pow(g_v,2))*(massElectron * T / pow(Enu,2));
  
    XC *= Sigma0 ;

    //  Add term due to neutrino magnetic moment.
    static const double alphainv = 1./CLHEP::fine_structure_const;
    if (T > 0.) XC += (M_PI / pow(alphainv,2) * pow(vMu,2) / pow(massElectron,2)) * (1. - T/Enu)/T;

    //  Convert to detector units and return.
    XC *= XCunits;

    return XC;
  }

  void ESgen::SetXSecMax(int ntry)
  {
    double xMax = XMaxDefault;

    for(int i = 0; i < ntry+1; i++)
      {
	double Enu = GetRandomNumber(0.,10.);
	double T = GetRandomNumber(0.,Enu);    
	double xsec = GetXSec(Enu,T);    
	if (xsec > xMax) xMax = xsec;    
      }

    XSecMax = xMax;
    SetNormFlag(true);
  }

  double ESgen::GetRandomNumber(double rmin, double rmax)
  {
    double rnd = G4UniformRand(); // random number from 0 to 1.
    double value = rmin + (rmax - rmin) * rnd;
    return value;
  }

} // namespace RAT
