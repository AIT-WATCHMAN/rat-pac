

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)

   BONSAI_DIR := build/linuxx8664gcc/fit/bonsai

   OUT_DIR    := build/linuxx8664gcc

endif

ifeq ($(UNAME_S),Darwin)

   BONSAI_DIR := build/macosx64/fit/bonsai

   OUT_DIR    := build/macosx64

endif



CSCONS := CXXFLAGS=-std=c++11 scons

# Note: I plan to eventually get rid of scons and setup this makefile to

# handle everything.



all: bonsai

	$(CSCONS)

	ln -sf ../$(OUT_DIR)/RAT_Dict_rdict.pcm lib/RAT_Dict_rdict.pcm



bonsai:

	mkdir -p $(BONSAI_DIR)

	gfortran -c src/fit/bonsai/lfariadne.F -o $(BONSAI_DIR)/lfariadne.o



installdata:

	$(CSCONS) installdata



doc:

	$(CSCONS) doc



clean:

	$(CSCONS) -c



.PHONY: doc clean installdata all
