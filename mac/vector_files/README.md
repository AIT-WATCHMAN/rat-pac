# Vector from files
Read in macros directly into the command line in rat by executing
```
rat watchman_fastneutrons.mac -x fast_neutrons.dat
```
RAT will read through the file until either the number of events
specified by `/run/beamOn` is reached or the end-of-file is reached.
