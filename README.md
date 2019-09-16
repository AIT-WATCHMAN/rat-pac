# RAT (is an Analysis Tool), Public Edition

RAT is a simulation and analysis package built with GEANT4, ROOT, and C++,
originally developed by S. Seibert for the Braidwood Collaboration. Versions
of RAT are now being used and developed by several particle physics
experiments.

RAT combines simulation and analysis into a single framework, which allows
analysis code to trivially access the same detector geometry and physics
parameters used in the detailed simulation.

RAT follows the "AMARA" principle: As Microphysical as Reasonably Achievable.
Each and every photon is tracked through an arbitrarily detailed detector
geometry, using standard GEANT4 or custom physics processes. PMTs are fully
modeled, and detected photons may be propagated to a simulation of front-end
electronics and DAQ.

This generic version is intended as a starting point for collaborations
looking for an easy-to-learn, extensible detector simulation and analysis
package that works out of the box. Once acquainted with RAT, it is easy to
customize the geometry elements, physics details, data structure, analysis
tools, etc., to suit your experiment's needs.


## Installation

Installation requires [ROOT](https://root.cern.ch), [Geant4](https://geant4.web.cern.ch/), and [cmake 3.11+](https://cmake.org/)

Install using cmake

    $ git clone https://github.com/AIT-WACTHMAN/ratpac
    $ cd ratpac 
    $ mkdir build
    $ cd build
    $ cmake ../
    $ cmake --build . -- -j$(nproc)

If you want to install the code, just add

    $ cmake --build . --target install -j$(nproc)

## Docker

We have a docker image with rat pre-installed at
[morganaskins/ratpac](hub.docker.com/r/morganaskins/ratpac)

In this current implementation, any branched merged into the master version of
the github will automatically be uploaded to the docker image.

The correct work procedure is to fork the repository to your personal
directory. Make required changes. Make pull request by assigning a approved
custodian.

Please note that another github exist for WATCHMAN work:
https://github.com/AIT-WACTHMAN/watchmakers. Within that github are tools to
call docker image functions from the users terminal.
