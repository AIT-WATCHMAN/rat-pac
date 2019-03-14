BONSAI_DIR := build/linuxx8664gcc/fit/bonsai
CSCONS := CXXFLAGS=-std=c++11 scons

all: bonsai
	$(CSCONS)

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
