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

/* ********************************************
   formatting.cpp
   coded by David Miller
   mill2723 at msu dot edu

   contains functions for formatting lattices
   in various ways

**********************************************/

#include "header.h"
#include "dec.h"

using namespace std;

//formats the structure such that the 1st atom is at 0,0,0
void formatUnit(Structure& syst)
{
  Lattice lat = syst.getLattice();	      
  
  vector<double> pos;
  vector<double> frac;
  
  Atom atom;
  
  for (unsigned i = 0; i < syst.size(); i++)
    {
      atom = syst[i];
      pos = atom.Position();
      calcFracVector(lat,pos,frac);
      for (unsigned j = 0; j < 3; j++)
	{
	  while (frac[j] < 0.0)
	    {
	      frac[j] += 1.0;
	    }
	  while (frac[j] > 1.0)
	    {
	      frac[j] -= 1.0;
	    }
	}
      calcCartVector(lat,pos,frac);
      atom.setPosition(pos);		      
      syst.changeAtom(i,atom);
    }
}

void formatLayered(Structure& syst)
{
  Lattice lat = syst.getLattice();	      
  
  vector<double> pos(3, 0.0);
  vector<double> frac(3, 0.0);
  
  Atom atom;
  
  for (unsigned i = 0; i < syst.size(); i++)
    {
      atom = syst[i];
      pos = atom.Position();
      calcFracVector(lat,pos,frac);
    
      while (frac[2] <-0.5)
	{
	  frac[2] += 1.0;
	  //cout << "Frac vec incremented" << endl;
	}
      while (frac[2] > 0.5)
	{
	  frac[2] -= 1.0;
	  //cout << "Frac vec decremented" << endl;
	}

      calcCartVector(lat,pos,frac);
      atom.setPosition(pos);		      
      syst.changeAtom(i,atom);
    }
}

//this should shift the structure so that atom number index is at the origin
//this is most useful when combined with FormatUnit so that all the atoms lie in the unit cell
//syst is the structure that is being formatted
//index is the index of the atom to place at the origin
void formatShift(Structure& syst, unsigned index)
{
  //displays an error message if the index is larger than the size of the structure
  if (index > syst.size())
    {
      cerr << "Cannot shift to atom at index " << index << " as there are not that many atoms in the system." << endl;
      return;
    }
  //the atom to place at the origin 
  Atom atom_origin = Atom(), atom_current = Atom();
  
  //the vector the origin atom and the current vector position
  vector<double> vec_origin(3), vec_current(3);

  //the systems lattice
  Lattice lat = syst.getLattice();
  
  atom_origin = syst[index];
  vec_origin = atom_origin.Position();
  
  for (unsigned i = 0; i < syst.size(); i++)
    {
      atom_current = syst[i];
      vec_current = atom_current.Position();
      for (unsigned j = 0; j < 3; j++)
	{
	  vec_current[j] -= vec_origin[j];
	}
      atom_current.setPosition(vec_current);
      syst.changeAtom(i,atom_current);
    } 
}

void formatLattice(Structure &syst)
{

  //  cout << "
  Lattice tmpLat = Lattice(syst.getLattice());
  vector<double> latVec = vector<double>(tmpLat.getVector());
  cout << setprecision(10);
  
  for (unsigned i = 0; i < 3; i++)
    {
      cout << "Lattice[" << i << "]: " << latVec[i] << endl;
    }    

  for (unsigned i = 3; i < 6; i++)
    {
      cout << "Lattice[" << i << "]: " << radtodeg(latVec[i]) << endl;
    }


  bool CUBIC = false, TETRA = false, ORTHO = false, RHOMBO = false, HEX = false, MONO = false, TRI = false;
  
  //check if all angles are 90 degrees:
  // a - cubic - a=b=c -> do nothing 
  // b - tetragonal - a=b!=c -> make sure c is the unique axis
  // c - orthorhombic - a<b<c -> change ordering

  //check if a=b=c but angles != 90 degrees -> rhombohedral
  // nothing to do
  
  //check if two angles are 90 degrees
  // a=b, gamma=120 degrees? -> hexagonal, make unique axis c
  // else monoclinic -> a,b <= c, alpha < 90 degrees (reorient angles if > 90)

  //else triclinic and make use standard lattice

  //a=b=c
  if ( (abs(latVec[0] - latVec[1]) < EPS) && (abs(latVec[1] - latVec[2]) < EPS) )
    {
      //alpha=beta=gamma=90
      if ( (abs(latVec[3] - PI/2) < EPS) && (abs(latVec[4] - PI/2) < EPS) && (abs(latVec[5] - PI/2) < EPS) )
	{
	  CUBIC = true;
	}
      //alpha=beta=gamma!=90
      else
	{
	  RHOMBO = true;
	}
    }
  else
    {
      //alpha=beta=gamma=90
      if ( (abs(latVec[3] - PI/2) < EPS) && (abs(latVec[4] - PI/2) < EPS) && (abs(latVec[5] - PI/2) < EPS) )
	{
	  //a!=b!=c
	  if ( (abs(latVec[0] - latVec[1]) > EPS) && (abs(latVec[0] - latVec[2]) > EPS) && (abs(latVec[1] - latVec[2]) > EPS) )
	    {
	      ORTHO = true;
	    }
	  //a=b!=c
	  else
	    {
	      TETRA = true;
	    }
	}
      else
	{
	  //alpha=beta=90!=gamma
	  if ( ((abs(latVec[3] - PI/2) < EPS) && (abs(latVec[4] - PI/2) < EPS) ) || ((abs(latVec[4] - PI/2) < EPS) && (abs(latVec[5] - PI/2) < EPS) ) || ((abs(latVec[3] - PI/2) < EPS) && (abs(latVec[5] - PI/2) < EPS) ) )
	    {
	      if ( ( (abs(latVec[3] + latVec[4] + latVec[5] - (3*PI/2 + PI/6)) < EPS) || (abs(latVec[3]+ latVec[4] + latVec[5] - (PI + PI/3)) < EPS) ) && ( (abs(latVec[0] - latVec[1]) < EPS) || (abs(latVec[1] - latVec[2]) < EPS) || (abs(latVec[0] - latVec[2]) < EPS) ) )
		{
		  HEX = true;
		}
	      else
		{
		  MONO = true;
		}
	    }
	  else
	    {
	      TRI = true;
	    }
	}
    }

  cout << "Lattice classified..." << endl;
  cout << "Formatting..." << endl;
  //at this point the Bravais lattice should be determined;
  //CUBIC: do nothing
  if (CUBIC)
    cout << "CUBIC lattice." << endl;
  //RHOMBO: do nothing
  if (RHOMBO)
    cout << "RHOMBOHEDRAL lattice." << endl;

  //TETRA: order a=b,c
  if (TETRA)
    {
      cout << "TETRAGONAL lattice." << endl;
      if (abs(latVec[0] - latVec[2]) < EPS)
	syst.swapBravaisAxis(1,2);
      if (abs(latVec[1] - latVec[2]) < EPS)
	syst.swapBravaisAxis(0,2);
    }
  //ORTHO: order a<b<c
  if (ORTHO)
    {
      cout << "ORTHORHOMBIC lattice." << endl;
      if ( (latVec[0] < latVec[1]) && (latVec[0] < latVec[2]) )
	{
	  if (latVec[1] > latVec[2])
	    syst.swapBravaisAxis(1,2);
	}
      else
	{
	  if (latVec[1] < latVec[2])
	    {
	      syst.swapBravaisAxis(0,1);
	      if (latVec[0] > latVec[2])
		syst.swapBravaisAxis(1,2);
	    }
	  else
	    {
	      syst.swapBravaisAxis(0,2);
	      if (latVec[1] > latVec[0])
		syst.swapBravaisAxis(1,2);
	    }
	}
    }

  //HEX: order a=b,c AND alpha=beta=90,gamma=120;
  if (HEX)
    {
      cout << "HEXAGONAL lattice." << endl;
      if (abs(latVec[0] - latVec[2]) < EPS)
	syst.swapBravaisAxis(1,2);
      else
	if (abs(latVec[1] - latVec[2]) < EPS)
	  syst.swapBravaisAxis(0,2);
      
      //120 degrees case
      if ( (latVec[3] + latVec[4] + latVec[5]) > 3*PI/2)
	{
	  syst.swapBravaisAngle(0,1);
	}
     }
  
  //MONO: order a,b<=c AND alpha<90,beta=gamma=90;
  if (MONO)
    {
      cout << "MONOCLINIC lattice." << endl;
      if ( (latVec[0] > latVec[1]) && (latVec[0] > latVec[2]) )
	{
	  syst.swapBravaisAxis(0,2);
	  cout << "a is largest" << endl;
	}	
      else
	{
	  if (latVec[1] > latVec[2])
	    {
	      syst.swapBravaisAxis(1,2);
	      cout << "b is largest" << endl;
	    }
	  else
	    cout << "c is largest" << endl;
	}
      latVec = vector<double>(syst.getLattice().getVector());
      if ( (latVec[3] + latVec[4] + latVec[5]) > 3*PI/2)
	{
	  if (latVec[5] > PI/2)
	    {
	      syst.swapBravaisAngle(1,2);
	      syst.swapBravaisAxis(0,1);
	    }
	  else
	    {
	      if (latVec[4] > PI/2)
		{
		  syst.swapBravaisAxis(0,1);
		}
	      else 
		{
		  syst.swapBravaisAxis(0,1);
		  syst.swapBravaisAngle(0,1);
		}
	    }
	}
      else
	{
	  if (abs(latVec[5] - PI/2) > EPS )
	    syst.swapBravaisAngle(0,2);
	  if (abs(latVec[4] - PI/2) > EPS )
	    syst.swapBravaisAngle(0,1);
	}
	    
    }
  
  //TRI: do nothing
    if (TRI)
      cout << "TRICLINIC lattice." << endl;

    cout << setprecision(10);

    vector<double> newLatVec = vector<double>(syst.getLattice().getVector());
    for (unsigned i = 0; i < 3; i++)
      {
	cout << "New Lattice[" << i << "]: " << newLatVec[i] << endl;
      }
    for (unsigned i = 3; i < 6; i++)
      {
	cout << "New Lattice[" << i << "]: " << radtodeg(newLatVec[i]) << endl;
      }
}
