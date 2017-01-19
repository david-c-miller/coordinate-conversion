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

/* *******************************************
   Structure.cpp
   coded by David Miller
   mill2723 at msu dot edu

   
   Contains definitions of functions for the 
   Structure class
**********************************************/
#include "dec.h"

Structure::Structure(const Structure &istruct) : n(istruct.n), name(istruct.name), no_lattice(istruct.no_lattice)
{
   for (unsigned i = 0; i < n; i++)
    {
      p_Atoms[i] = Atom(istruct.p_Atoms[i]);
    }
  if (!(no_lattice))
    {
      lat = Lattice(istruct.lat);
    }
} 

Structure::Structure\
(const unsigned ni, const string iname, const Lattice &ilat)\
  : n(ni), name(iname), lat(ilat)
{}

Structure::Structure\
(const vector<Atom>& iatoms, const string iname, const Lattice& ilat)\
  : n(static_cast<unsigned>(iatoms.size())), name(iname), lat(ilat)
{
  p_Atoms.clear();
  for (unsigned i = 0; i < n; i++)
    {
      p_Atoms.push_back(iatoms[i]);
    }
}

Structure::~Structure()
{
}
 	
//returns the size
unsigned Structure::size()
{
  return n;
}

void Structure::clear()
{
  p_Atoms.clear();
  n = 0;
}
  
void Structure::addAtom(const Atom &new_atom)
{
  p_Atoms.push_back(new_atom);
  n++;
}

//returns the ith atom (zero indexed)
Atom Structure::getAtom(const unsigned i)
{
  if ( i >= n)
    {
      fprintf(stderr,"Error - out of bounds\n"); 
      throw -1;
    }
  else return p_Atoms[i];
} 

//replaces the atom at index (alternatively with a x,y,z triple
void Structure::changeAtom(const unsigned index, const Atom &new_atom)
{
  p_Atoms[index] = Atom(new_atom);
} 

Lattice Structure::getLattice()
{
  return lat;
}

void Structure::setLattice(const Lattice &ilat)
{
  lat = Lattice(ilat);
  no_lattice = false;
}

bool Structure::noLattice()
{
  if (abs(lat.getVector()[0]) < EPS || abs(lat.getVector()[1]) < EPS || abs(lat.getVector()[2]) < EPS) no_lattice = true;
  else no_lattice = false;
  return no_lattice;
} 
void Structure::removeLattice()
{
  vector<double> tmp = vector<double>(6,0.0);
  lat = Lattice(tmp);
  no_lattice = true;
} 

//over write name
void Structure::setName(const string iname)
{
  name = iname;
} 
void Structure::getName(string oname)
{
  oname = name;
} 

string Structure::Name()
{
  return name;
} 

/*
  returns the distance between two atoms (i and j) with 
  corrections for boundary (unless no_lattice is set and 
  then absolute distance)	
*/
double Structure::atomDistance(unsigned i, unsigned j)
{
  return Atom::getDistance(p_Atoms[i], p_Atoms[j]);
} 

//returns a vector from atom i to atom j
void Structure::atomVector(unsigned i, unsigned j, vector<double>& ovec)
{
  Atom::getVector(p_Atoms[i], p_Atoms[j], ovec);
} 
//double maxSeperation();

#if 0
/*
  returns the minimum and maximum values of x, y, and z
  respectivley (i.e. the max/min obtained by an atom in the
  structure)
*/
double Structure::xMin()
{
  return 0;
} 
double Structure::xMax()
{
  return 0;
} 

double Structure::yMin()
{
  return 0;
} 
double Structure::yMax()
{
  return 0;
} 

double Structure::zMin()
{
  return 0;
} 
double Structure::zMax()
{
  return 0;
} 
#endif

void Structure::getElementAtomList(const string ielem, vector<Atom>& olist)
{
  olist.clear();
  for (unsigned i = 0; i < n; i++)
    {
      if (ielem.compare(p_Atoms[i].Element()) == 0) olist.push_back(p_Atoms[i]);
    }

} 
void Structure::getElementTypes(vector<string>& olist, vector<unsigned>& ocount)
{
  olist.clear();
  ocount.clear();

  string tmp_elem;
  unsigned tmp_count;

  bool new_elem;

  for (unsigned i = 0; i < n; i++)
    {
      tmp_elem = p_Atoms[i].Element();
      new_elem = true;
      for (unsigned j = 0; j < olist.size(); j++)
	{
	  if (tmp_elem.compare(olist[j]) == 0)
	    {
	      new_elem = false;
	      break;
	    }
	}
      if (new_elem)
	{
	  olist.push_back(tmp_elem);
	  tmp_count = this->getCountElement(tmp_elem);
	  ocount.push_back(tmp_count);
	}
      tmp_count = 0;
      tmp_elem = "N/A";
    }
}

unsigned Structure::getCountElement(const string ielem)
{
  unsigned count = 0;
  for (unsigned i = 0; i < n; i++)
    {
      if (ielem.compare(p_Atoms[i].Element()) == 0) count++;
    }
  return count;     
}

void Structure::swapBravaisAxis(unsigned axisA, unsigned axisB)
{
  cout << "Swapping: " << axisA << " for " << axisB << endl;
  if ( (axisA > 2) || (axisB > 2) ) // || (axisA < 0) || (axisB < 0) )
    throw -1;
  if (axisA == axisB)
    throw -1;
  unsigned axisC = (3 - axisA - axisB);
  if ( (axisC > 2) ) //|| (axisC < 0) )
    throw -1;

  vector<double> oldVec = vector<double>(lat.getVector());
  vector<double> newVec = vector<double>(6,0.0);

  newVec[axisC] = oldVec[axisC];
  newVec[axisA] = oldVec[axisB];
  newVec[axisB] = oldVec[axisA];
  if (axisC == 0)
    {
      newVec[4] = oldVec[5];
      newVec[3] = PI - oldVec[3];
      newVec[5] = oldVec[4];
    }
  if (axisC == 1)
    {
      newVec[4] = PI - oldVec[4];
      newVec[3] = oldVec[5];
      newVec[5] = oldVec[3];
    }
  if (axisC == 2)
    {
      newVec[3] = oldVec[4];
      newVec[4] = oldVec[3];
      newVec[5] = PI - oldVec[5];
    }

  Lattice newLat = Lattice(newVec);
  Lattice oldLat = Lattice(lat);
  lat = Lattice(newLat);

  Atom oldAtom;
  vector<double> oldCoord = vector<double>(3,0.0);
  vector<double> oldFrac = vector<double>(3,0.0);
  vector<double> newFrac = vector<double>(3,0.0);
  vector<double> newCoord = vector<double>(3,0.0);
  
  for (unsigned i = 0; i < n; i++)
    {
      oldAtom = Atom(p_Atoms[i]);
      oldCoord = vector<double>(oldAtom.Position());
      calcFracVector(oldLat, oldCoord, oldFrac);
      
      newFrac[axisC] = oldFrac[axisC];
      newFrac[axisA] = oldFrac[axisB];
      newFrac[axisB] = 1 - oldFrac[axisA];

      calcCartVector(newLat, newCoord, newFrac);

      p_Atoms[i].setPosition(newCoord);
    }
}

void Structure::swapBravaisAngle(unsigned angleA, unsigned angleB)
{
  cout << "Swapping Angles: " << angleA+3 << " for " << angleB+3 << endl;
  if ( (angleA > 2) || (angleB > 2) ) 
    throw -1;
  if (angleA == angleB)
    throw -1;
  unsigned angleC = (3 - angleA - angleB);
  if ( (angleC > 2) ) //||  (angleC < 0) )
    throw -1;

  vector<double> oldVec = vector<double>(lat.getVector());
  vector<double> newVec = vector<double>(6,0.0);

  newVec[angleC+3] = oldVec[angleC+3];
  newVec[angleA+3] = oldVec[angleB+3];
  newVec[angleB+3] = oldVec[angleA+3];

  if (angleC == 2)
    {
      newVec[2] = oldVec[2];
      newVec[0] = oldVec[1];
      newVec[1] = oldVec[0];
    }
  if (angleC == 1)
    {
      newVec[1] = oldVec[1];
      newVec[0] = oldVec[2];
      newVec[2] = oldVec[0];
    }
  if (angleC == 0)
    {
      newVec[0] = oldVec[0];
      newVec[2] = oldVec[1];
      newVec[1] = oldVec[2];
    }
  
  Lattice newLat = Lattice(newVec);
  Lattice oldLat = Lattice(lat);
  lat = Lattice(newLat);

  Atom oldAtom;
  vector<double> oldCoord = vector<double>(3,0.0);
  vector<double> oldFrac = vector<double>(3,0.0);
  vector<double> newFrac = vector<double>(3,0.0);
  vector<double> newCoord = vector<double>(3,0.0);
  
  for (unsigned i = 0; i < n; i++)
    {
      oldAtom = Atom(p_Atoms[i]);
      oldCoord = vector<double>(oldAtom.Position());
      calcFracVector(oldLat, oldCoord, oldFrac);
      
      newFrac[angleC] = 1 - oldFrac[angleC];
      newFrac[angleA] = oldFrac[angleB];
      newFrac[angleB] = oldFrac[angleA];

      calcCartVector(newLat, newCoord, newFrac);

      p_Atoms[i].setPosition(newCoord);
    }
}
