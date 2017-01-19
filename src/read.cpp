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
   read.cpp
   coded by David Miller
   mill2723 at msu dot edu

   Contains functions for reading in various 
   different formats. To add a new format for
   read and write capabilities, you should 
   make write and read functions and put the
   read function here.
**********************************************/

#include "dec.h"

namespace Read
{
  int readXYZ(Structure& syst, istream& ist)
  {
    string name, lbuf;
    stringstream sbuf;

    int num_atoms;

    syst.clear();
    sbuf << setprecision(10);

    getline(ist,lbuf);
    sbuf.str(lbuf);

    sbuf >> num_atoms;
    sbuf.clear();

    getline(ist,name);
    syst.setName(name);

    vector<double> pos_list(3);
    string elem_list;
    for (int i = 0; i < num_atoms; i++)
      {
	getline(ist,lbuf);
	sbuf.str(lbuf);
	sbuf >> elem_list >> pos_list[0] >> pos_list[1] >> pos_list[2];

	syst.addAtom(Atom(elem_list, pos_list));
	sbuf.clear();
      }

    return 0;
  }

  //reads in a VASP style POSCAR file
  //this needs to be able to tell the difference between
  //direct (fractional) and cartesian coordinates
  int readVASP(Structure& syst, istream& ist)
  {
    string name, lbuf;
    size_t posStart, posFind, posEnd;
    stringstream sbuf;

    unsigned numElem;

    double scale;
    vector< vector<double> > latMat(3, vector<double>(3,0.0));
    Lattice lat;

    vector<string> elemList;
    vector<unsigned> elemCount;
    vasp::CoordinateFormat format;

    Atom inAtom;

    vector<double> coord(3), tcoord(3);

    syst.clear();
    //ist << setprecision(10);
    sbuf << setprecision(10);

    getline(ist, name);
    // cout << "Read name: " << name << endl;
    //getline(ist, lbuf);

    //sbuf = stringstream(lbuf);
    //sbuf >> scale;

    getline(ist,lbuf);
    sbuf.str(lbuf);
    sbuf >> scale;
    //cout << "Read scale: " << scale << endl;
    sbuf.clear();

    //get the lattice vectors
    for (unsigned i = 0; i < 3; i++)
      {
	getline(ist,lbuf);
	sbuf.str(lbuf);
	cout << "Line " << i << ": " << sbuf.str() << endl;
	for (unsigned j = 0; j < 3; j++)
	  {
	    sbuf >> latMat[i][j];
	  }
	sbuf.clear();
      }

    // cout << "Print lattice vectors: " << endl;
    /* 
      for (int i = 0; i < 3; i++)
       {
	for (int j = 0; j < 3; j++)
	  {
	    	    cout << latMat[i][j] << "\t";
	  }
	cout << endl;
      }
    //*/

    //if scaled, multiply the lattice vectors by the scale
    cout << "Scaling factor: " << scale << endl;
    if ( abs(scale - 1.0) > EPS ) 
      {
	for (unsigned i = 0; i < 3; i++)
	  {
	    for (unsigned j = 0; j < 3; j++)
	      {
		latMat[i][j] *= scale;
	      }
	  }
      }
    //store the lattice vector in a lattice struct
    lat = Lattice(latMat);

    ///*
    cout << "Print lattice vectors: " << endl;
    for (unsigned i = 0; i < 3; i++)
      {
	for (unsigned j = 0; j < 3; j++)
	  {
	    cout << lat.getMatrix()[i][j] << "\t";
	  }
	cout << endl;
      }
    //*/

    //get the list of elements
    getline(ist, lbuf);
    //cout << "Element list string: " << lbuf << endl;
    posStart = 0;
    while(posStart < lbuf.size())
      {
	posFind = lbuf.find_first_not_of(" \t", posStart);
	if (posFind == string::npos) break;
	posEnd = lbuf.find_first_of(" \t\n", posFind);
	if (posEnd == string::npos) posEnd = lbuf.size();
	elemList.push_back(lbuf.substr(posFind,posEnd));
	posStart = posEnd;      
      }

    numElem = static_cast<unsigned>(elemList.size());
    if (numElem == 0)
      {
	cerr << "Error: no elements found in VASP file.\nPlease check the file and try again." << endl;
	return 1;
      }

    /*
      cout << "Elements read: " << numElem << endl;
    for (unsigned i = 0; i < numElem; i++)
      {
	cout << elemList[i] << "\t";
      }
    cout << endl;
    */

    unsigned totalAtomCount = 0;

    getline(ist, lbuf);
    sbuf.str(lbuf);
    unsigned tmp;
    for (unsigned i = 0; i < numElem; i++)
      {
	sbuf >> tmp;
	elemCount.push_back(tmp);
	totalAtomCount += tmp;
      }
    sbuf.clear();
    //cout << "Atoms to read: " << totalAtomCount << endl;

    getline(ist,lbuf);

    posFind = lbuf.find_first_not_of(" \t");
    if (posFind == string::npos) 
      {
	cerr << "Error: no Direct or Cartesian statement found.\nPlease check the file and try again." << endl;
	return -1;
      }
    if (lbuf[posFind] == 'D' || lbuf[posFind] == 'd')
      format = vasp::Direct;
    else
      {
	if (lbuf[posFind] == 'C' || lbuf[posFind] == 'c')
	  format = vasp::Cartesian;
	else
	  {
	    cerr << "Error: Incorrect specification of coordinate format." << endl;
	    return -1;
	  }
      }

    for (unsigned i = 0; i < numElem; i++)
      {
	for (unsigned j = 0; j < elemCount[i]; j++)
	  {
	    getline(ist,lbuf);
	    sbuf.str(lbuf);
	    for (unsigned w = 0; w < 3; w++)
	      {
		sbuf >> coord[w];
	      }
	    sbuf.clear();
	    if (format == vasp::Direct)
	      {
		tcoord = vector<double>(coord);
		calcCartVector(lat,coord,tcoord);
	      }

	    inAtom = Atom(elemList[i],coord[0], coord[1], coord[2]);

	    syst.addAtom(inAtom);
	  }
      }

    syst.setName(name);

    syst.setLattice(lat);

    return 0;
  }

#if 0
  int readPDB(Structure& syst, istream& ist)
  {
    return 1;
  }
#endif

#if 0
  int readCOORD(Structure& syst, istream& ist)
  {
    string name, lbuf, junk;
    stringstream sbuf;

    int numElem;

    double scale;
    vector< vector<double> > latMat(3, vector<double>(3,0.0));
    Lattice lat;

    char elem[2];
    vector<string> elemList;
    vector<int> elemCount;
    vasp::CoordinateFormat format;

    Atom inAtom;

    vector<double> coord(3), tcoord(3);

    syst.clear();
    getline(ist,name); 

    for (unsigned i = 0; i < 3; i++)
      {
	getline(ist,lbuf);
	sbuf.str(lbuf);
	sbuf >> junk >> latMat[i][0] >> latMat[i][1] >> latMat[i][2];

	sbuf.clear();
      }

    //need to read in each element and the number of atoms
    //then read in the total number of positions from there

    return 1;
  }
#endif
}
