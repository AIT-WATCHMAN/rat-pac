BONSAI_DIR := build/linuxx8664gcc/fit/bonsai
CSCONS := CXXFLAGS=-std=c++11 scons
# Note: I plan to eventually get rid of scons and setup this makefile to
# handle everything.

all: bonsai
	$(CSCONS)
	ln -sf ../build/linuxx8664gcc/RAT_Dict_rdict.pcm lib/RAT_Dict_rdict.pcm

bonsai:
	mkdir -p $(BONSAI_DIR)
	gfortran -c src/fit/bonsai/lfariadne.F -o $(BONSAI_DIR)/lfariadne.o
	$(MAKE) -C tools/bonsai

installdata:
	$(CSCONS) installdata

doc:
	$(CSCONS) doc

clean:
	$(CSCONS) -c

.PHONY: doc clean installdata all
