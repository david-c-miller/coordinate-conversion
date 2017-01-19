/*
  Copyright 2016-2017 David C. Miller

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

/* *************************************************************
   Structure.h
   written by David Miller
   mill2723 at msu dot edu
   
   Contains definitions for Structure class which contains a
   series of atoms at various locations

*****************************************************************/
#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "header.h"
#include "Atom.h"
#include "Lattice.h"

using namespace std;

class Structure
{
private:
  /*
    n: number of atoms
    lat: lattice parameters
    p_Atoms: vector of atoms
    name: name of structure
    no_lattice: whether lattice_param is set
  */
  unsigned n;
  string name;
  bool no_lattice;
  Lattice lat;
  vector<Atom> p_Atoms; 

public:
  Structure(const Structure &istruct); 
  Structure(const unsigned ni = 0, const string\
	    iname = "Default", const Lattice &ilat = Lattice());
  Structure(const vector<Atom>& iatoms, const string\
	    iname = "Default", const Lattice &ilat = Lattice());

  ~Structure();
  //returns the size
  unsigned size() __attribute__ ((pure));
  
  //access the ith atom
  Atom operator[](unsigned i)
  {
    if (i <= n) 
	return p_Atoms[i];
    else
	throw -1;
  }

  void clear();
  void addAtom(const Atom &new_atom);

  //returns the ith atom (zero indexed)
  Atom getAtom(const unsigned i);

  //replaces the atom at index (alternatively with a x,y,z triple
  void changeAtom(const unsigned index, const Atom &new_atom);

  //gets or sets the lattice parameter
  Lattice getLattice();
  void setLattice(const Lattice &ilat);
  
  bool noLattice();
  void removeLattice();

  //prints atoms (to stdout)
  //void printAtoms();

  //over write name
  void setName(const string iname);
  void getName(string oname);

  string Name();

  //returns the distance between two atoms (i and j) with corrections for boundary (unless no_lattice is set and then absolute distance)	
  double atomDistance(unsigned i, unsigned j);

  //returns a vector from atom i to atom j
  void atomVector(unsigned i, unsigned j, vector<double>& ovec);
  //double maxSeperation();

  //returns the minimum and maximum values of x, y, and z respectivley (i.e. the max/min obtained by an atom in the structure)
  double xMin();
  double xMax();

  double yMin();
  double yMax();

  double zMin();
  double zMax();

  void getElementAtomList(const string ielem, vector<Atom> &olist);
  void getElementTypes(vector<string> &olist, vector<unsigned> &ocount);
  unsigned getCountElement(const string ielem);

  void swapBravaisAxis(unsigned axisA, unsigned axisB);
  void swapBravaisAngle(unsigned angleA, unsigned angleB);
  
};

#endif
