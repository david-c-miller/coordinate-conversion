#!/usr/bin/make

#############################################################################
#  Copyright 2016-2017 David C. Miller                                           #
#                                                                           #
#  Licensed under the Apache License, Version 2.0 (the "License");          #
#  you may not use this file except in compliance with the License.         #
#  You may obtain a copy of the License at                                  #
#                                                                           #
#  http://www.apache.org/licenses/LICENSE-2.0                               #
#                                                                           #
#  Unless required by applicable law or agreed to in writing, software      #
#  distributed under the License is distributed on an "AS IS" BASIS,        #
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. #
#  See the License for the specific language governing permissions and      #
#  limitations under the License.                                           #
#############################################################################

# Makefile
# defines all rules and should not be edited
# except as necessary

include makefile.include

#########################
#   Local Directories   #
#########################

#intentionally blank
DIRLIST =

#code directories
ODIR = obj
BDIR = bin
IDIR = inc
SDIR = src

DIRLIST += $(ODIR) $(BDIR) $(IDIR) $(SDIR)

CXXSUFFIX=.cpp

BINC=$(CXX)
BINSUFFIX=$(CXXSUFFIX)
BINFLAGS=$(CXXFLAGS)

OFLAG=$(OFLAG_DEBUG)
#specific flags
CXXFLAGS=$(CXXFLAGS_DEBUG)

#working directory
MAINDIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

_OBJ = $(patsubst %.o,%$(CXXSUFFIX).o,$(_CXXOBJ))

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#build
BIN = $(patsubst %,$(BDIR)/%,$(_BIN))

##########################################################################
# Do not change anything below here (unless you know what you're doing)  #
##########################################################################

.PRECIOUS: $(ODIR)/%$(CXXSUFFIX).o\

.PHONY: all
all: $(BIN)

#prog
$(ODIR)/%$(CXXSUFFIX).o: $(SDIR)/%$(CXXSUFFIX) $(DEPS) $(CLASS)
	$(CXX) -c -o $@ $< $(FLAGS_BASE) $(OFLAG) $(LDFLAGS) $(CXXFLAGS)

$(BDIR)/%: $(OBJ) $(ODIR)/%$(BINSUFFIX).o
	$(BINC) $^ $(FLAGS_BASE) $(OFLAG) $(LDFLAGS) $(BINFLAGS) -o $@

#clean up
CLEAN_CMD = rm -f *~;
RESET_CMD =
CLEAN_CMD += rm -f $(ODIR)/* $(IDIR)/*~ $(SDIR)/*~;
RESET_CMD += rm -f $(BDIR)/*;

.PHONY: clean reset dir
clean:
	$(CLEAN_CMD)

reset: clean
	$(RESET_CMD)

dir:
	mkdir -p $(DIRLIST)

#force specific flags
.PHONY: debug final install uninstall link
debug: reset
	make all CFLAGS="$(CFLAGS_DEBUG)" OFLAG="$(OFLAG_DEBUG)"

final: reset
	make all CFLAGS="$(CFLAGS_FINAL)" OFLAG="$(OFLAG_FINAL)"

#install and make links in default bin directory
link: uninstall
	ln -s $(MAINDIR)/bin/* $(INSTALLDIR)/

install: final uninstall
	cp $(MAINDIR)/bin/* $(INSTALLDIR)/

uninstall:
	cd $(INSTALLDIR)/ && rm -f $(_BIN);
	cd $(MAINDIR);
