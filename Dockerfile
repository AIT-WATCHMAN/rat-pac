# Use the base image with geant4 and root prebuilt.

FROM aitwatchman/simulation:base
MAINTAINER Morgan Askins "maskins@berkeley.edu"

# Run commands as super user
USER root

# Update rat-pac to latest version
RUN cd /src/rat-pac \
  && git pull \
  && gfortran -c src/fit/bonsai/lfariadne.F -o build/linuxx8664gcc/fit/bonsai/lfariadne.o \
  #&& CXXFLAGS=-std=c++11 scons \
  && scons \
  && cd /src/rat-pac/tools/bonsai \
  && make

# Update {other repos here}
RUN cd /src/watchmakers \
  && git pull \
  && git remote -v \ 
  && mkdir -p /docker_interaction_software \
  && rsync -avz /src/watchmakers/tools/d* /docker_interaction_software/



# Copy dockerfile for record
COPY Dockerfile Dockerfile
