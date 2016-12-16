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

/* ******************************************************
   write.cpp
   coded by David Miller
   mill2723 at msu dot edu

   This contains all write functions used throughout
   this project. To add new functionality to the project
   you should add a new write and read functions storing
   the write function here.

********************************************************/

#include "dec.h"

namespace Write
{
  /*
    .xyz format is very simple
    the first line specifies the number of atoms in the structure
    the second line is a comment, typically contains the name and the units
    finally each atom is given by the element, and then x, y, and z coordinates
  */
  int writeXYZ(Structure& syst, ostream& ost)
  {
    ost << syst.size() << endl;
    ost << syst.Name() << " (in angstroms)" << endl;

    ost << fixed << setprecision(6);
    for (unsigned i = 0; i < syst.size(); i++)
      {
	ost << syst[i].Element() << "\t" << syst[i][0] << "\t" << syst[i][1] << "\t" << syst[i][2] << endl;
      }
    return 0;
  }

  /*
    the VASP format is as follow
    the first line is a comment, typically the name of the system
    next is the 3 lattice vectors
    then the elements are listed in a single line
    the following line contains an integer with the number of atoms per species for
    each species list previously
    finally a specification of cartesian or direct coordinates is given
    followed by the coordinates in order of species with just x, y, z or u,v,w
    values given
  */
  int writeVASP(Structure& syst, ostream& ost)
  {
    if (syst.noLattice())
      { 
	cerr << "Error, cannot print VASP format without lattice parameters.\nPlease set lattice parameters and retry.\n";
	return 0;
      }

    ost << fixed << setprecision(10);

    vector< vector<double> > latMat = syst.getLattice().getMatrix();
    vector<string> elemList;
    vector<unsigned> elemCount;

    syst.getElementTypes(elemList, elemCount);
    unsigned numElem = static_cast<unsigned>(elemList.size());

    ost << syst.Name() << endl; 
    ost << 1.0 << endl;

    for (unsigned i = 0; i < 3; i++) ost << "    " << latMat[i][0] << "    " << latMat[i][1] << "    " << latMat[i][2] << endl;

    ost << "    ";

    for (unsigned i = 0; i < numElem; i++) ost << elemList[i] << "    "; 

    ost << "\n    "; 
    for (unsigned i = 0; i < numElem; i++) ost << elemCount[i] << "    "; 
    ost << endl; 

    ost << "Cartesian" << endl;

    string curElem;
    unsigned curCount;
    vector<Atom> atomList;
    //vector<double> cartPos = vector<double>(3,0.0);
    vector<double> directPos = vector<double>(3,0.0);

    for (unsigned i = 0; i < numElem; i++)
      {
	curElem = elemList[i];
	curCount = elemCount[i];
	syst.getElementAtomList(curElem, atomList);

	for (unsigned j = 0; j < curCount; j++)
	  {
	    calcFracVector(syst.getLattice(),atomList[j].Position(),directPos);
	    //ost << " " << directPos[0] << "    " << directPos[1] << "    " << directPos[2] << endl;
	    ost << " " << atomList[j][0] << "\t" << atomList[j][1] << "\t" << atomList[j][2] << endl;
	  }
      }

    return 1;
  }

#if 0
  //this will be implemented to output a simple .fe file with edges and vertices
  int writeFE(Structure& syst, ostream& ost )
  {
    return 0;
  }

  //pdb files are not necessarily a useful implmentation since vmd, vesta, and other
  //programs can convert between these and xyz files
  int writePDB(Structure& syst, ostream& ost )
  {
    return 0;
  }
#endif

  int writeSIESTA(Structure& syst, ostream& ost )
  {
    vector<Atom> atomList;
    vector<string> elemList;
    vector<unsigned> elemCount;

    syst.getElementTypes(elemList, elemCount);

    ost << fixed << setprecision(6);
    ost << "#System: " << syst.Name() << endl;

    //print out scaling constant (1 angstrom)
    ost << "LatticeConstant 1.0 Ang" << endl;

    //print out input format
    ost << "AtomicCoordinatesFormat Ang" << endl;

    //if lattice parameters are set print it out in a data block
    if (!(syst.noLattice()))
      {
	vector<double> lat;
	lat = vector<double>(syst.getLattice().getVector());
	lat[3] = radtodeg(lat[3]);
	lat[4] = radtodeg(lat[4]);
	lat[5] = radtodeg(lat[5]);

	ost << "\n%block LatticeParameters\n"
	     << "\t" << lat[0] << "\t" << lat[1] << "\t" << lat[2] 
	     << "\t" << lat[3] << "\t" << lat[4] << "\t" << lat[5] 
	     << "\n" << "%endblock LatticeParameters\n" << endl;
      }

    //print out the actual coordinates
    //first prints out a commented key for which atom is which number
    //since SIESTA uses a number to represent each atom inside the coordinates and not the atomic symbol/number this is necessary

    ost << "#Atomic Key:\t";
    for (unsigned i = 0; i < elemList.size(); i++)
      {
	ost << elemList[i] << " = " << i+1 << "\t";
      }
    ost << endl;
    ost << endl;

    ost << "%block AtomicCoordinatesAndAtomicSpecies\n";
    for (unsigned i = 0; i < elemList.size(); i++)
      {
	syst.getElementAtomList(elemList[i], atomList);
	for (unsigned j = 0; j < atomList.size(); j++)
	  {
	    ost << atomList[j][0] << "\t" << atomList[j][1] << "\t" << atomList[j][2] << "\t" << i+1 << endl;
	  }
      }

    ost << "%endblock AtomicCoordinatesAndAtomicSpecies" << endl;
    ost << endl;
    ost << "#to use this file just include the following line inside the .fdf file.\n";
    ost << "#%include this_file_name.fdf" << endl;

    return 1;
  }

  int writeCOORD(Structure& syst, ostream& ost) 
  {
    vector< vector<double> > latMat = syst.getLattice().getMatrix();
    vector<string> vecName;
    vecName.push_back("a: ");
    vecName.push_back("b: ");
    vecName.push_back("c: ");

    vector<Atom> atomList;
    vector<string> elemList;
    vector<unsigned> elemCount;

    ost << fixed << setprecision(6);

    if (syst.noLattice())
      { 
	cerr << "Error, cannot print COORD format without lattice parameters.\nPlease set lattice parameters and retry." << endl;;
	throw -1;
      }

    // syst.getLattice(latVec);
    // convertLatticeVecMat(latMat, latVec);

    ost << syst.Name() << endl;

    ost << endl;

    for (unsigned i = 0; i < 3; i++) ost << vecName[i] << latMat[i][0] << "\t" << latMat[i][1] << "\t" << latMat[i][2] << endl;

    syst.getElementTypes(elemList, elemCount);

    ost << endl;

    //ost << elemList.size() << " elements and " << syst.size() << " atoms total." << endl;

    for (unsigned i = 0; i < elemList.size(); i++)
      {
	syst.getElementAtomList(elemList[i],atomList);

	for (unsigned j = 0; j < atomList.size(); j++)
	  {
	    ost << elemList[i] << (j+1) << "\t\t" << atomList[j][0] << "\t" << atomList[j][1] << "\t" << atomList[j][2] << endl;
	  }
      }

    return 1;
  }
}
