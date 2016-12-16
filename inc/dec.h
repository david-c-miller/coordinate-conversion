/*
  Copyright 2016 David C. Miller

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

/* ************************************************
   dec.h
   coded by David Miller
   mill2723 at msu dot edu

   contains all declarations for the project
   including constants and functions used

***************************************************/

#ifndef DEC_H
#define DEC_H

#include "header.h"
#include "exceptions.h"
#include "elements.h"

#include "Atom.h"
#include "Lattice.h"
#include "Structure.h"
#include "Handle.h"

using namespace std;

#ifndef GLOBAL_EXIT_CODES
#define GLOBAL_EXIT_CODES

namespace Exit
{
  enum ExitCode { Normal = 1, Error = -1, IO_Error = -10, Development = 0, Retry = 2 };
  enum ExceptionCode { Unknown = -1, Default = 1, IO_Excep = 2, Caught_Excep = 100 }; 
}

#endif

//variables
#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES
const double PI = 4*atan(1);
const double EPS = 10E-4;

const int version_major = 0;
const int version_minor = 4;
const int version_rev   = 0;

#endif

#ifndef ENUMS
#define ENUMS
namespace vasp
{
  enum CoordinateFormat {Direct, Cartesian};
}

#endif

//defines functions
#ifndef FUNCTIONS
#define FUNCTIONS

//functions
namespace Write
{
  int writeXYZ(Structure& syst, ostream& ost);
  int writeVASP(Structure& syst, ostream& ost);
  int writeFE(Structure& syst, ostream& ost);
  int writePDB(Structure& syst, ostream& ost);
  int writeSIESTA(Structure& syst, ostream& ost);
  int writeCOORD(Structure& syst, ostream& ost);
}

namespace Read
{
  int readXYZ(Structure& syst, istream& ist);
  int readVASP(Structure& syst, istream& ist);
  int readPDB(Structure& syst, istream& ist);
  int readCOORD(Structure& syst, istream& ist);
}

int handle_core_ops(unsigned argc, char* argv[], const Handle& op_handle);
void printUsage(string binName) __attribute__ ((pure));

namespace Vector
{
  double Norm(const vector<double> ivec) __attribute__ ((pure));
  double Dot(const vector<double>& ia, const vector<double>& ib) __attribute__ ((pure));
  double Angle(const vector<double>& ia, const vector<double>& ib)  __attribute__ ((pure));
  vector<double> Cross(const vector<double>& ia, const vector<double>& ib) __attribute__ ((pure));
 
}

void formatUnit(Structure& syst);
void formatShift(Structure& syst, unsigned index = 0);
void formatLayered(Structure& syst);
void formatLattice(Structure& syst);

void calcFracVector(const Lattice& ilat, const vector<double>& icoord, vector<double>& ofrac);
void calcCartVector(const Lattice& ilat, vector<double>& ocoord, const vector<double>& ifrac);

double degtorad(double deg) __attribute__ ((pure));
double radtodeg(double rad) __attribute__ ((pure));

string version(int major, int minor, int rev) __attribute__ ((pure));

#endif

#ifndef DEFAULT_HANDLES
#define DEFAULT_HANDLES

namespace Default
{
  const Handle vaspcoord(Read::readVASP, Write::writeCOORD,\
			 "vasp2coord", "Converts a VASP coordinate file to a human readable format.");
  const Handle vaspsiesta(Read::readVASP, Write::writeSIESTA,\
			  "vasp2siesta", "Converts a VASP coordinate file to SIESTA format for include in a .fdf file.");
  const Handle vaspxyz(Read::readVASP, Write::writeXYZ,\
		       "vasp2xyz", "Converts a VASP coordinate file to XYZ format.");
  const Handle xyzsiesta(Read::readXYZ, Write::writeSIESTA,\
			 "xyz2siesta", "Converts an xyz file to SIESTA .fdf format without lattice information.");
  const Handle vaspvasp(Read::readVASP, Write::writeVASP,\
			"vasp2vasp", "Corrects the lattice parameters on VASP coordinates to those used for band structure calculations and Brillouin zones. Use with the --bravais option to correctly output different lattices.");
}

#endif

#endif
