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

//Atom.h
//contains declaration of Atom struct
//#ifndef ATOM_CLASS
//#define ATOM_CLASS
#pragma once

#include "header.h"

using namespace std;

class Atom
{
private:
  string element;
  double px;
  double py;
  double pz;

public:
  // double x();
  //double y();
  //double z();
		
  double operator[](int i)
  {
    if (i == 0) return px;
    if (i == 1) return py;
    if (i == 2) return pz;

    return 0.0;
  }	

  explicit Atom(const string ielem = "N/A", const double ix = 0, const double iy = 0, const double iz = 0);	
  Atom(const Atom &ai);
  Atom(const string ielem, const vector<double> ivec);

  ~Atom();
  
  void setPosition(vector<double>& ivec);
  vector<double> Position();

  void setElement(string ielem);
  void getElement(string oelem);

  string Element();

  static double getDistance(const Atom& a1, const Atom& a2)
  {
    return sqrt( (a1.px-a2.px)*(a1.px-a2.px) + (a1.py-a2.py)*(a1.py-a2.py) + (a1.pz-a2.pz)*(a1.pz-a2.pz) );
  }
		
  /* //may choose to use again at some point
static double getDistance(const Atom &a1, const Atom a2, double bound)
  {
    double Dx, Dy, Dz;
    Dx = abs(a1.px - a2.px);
    Dy = abs(a1.py - a2.py);
    Dz = abs(a1.pz - a2.pz);
			
    if (Dx > bound) Dx = (2*bound - Dx);
    if (Dy > bound) Dy = (2*bound - Dy);
    if (Dz > bound) Dz = (2*bound - Dz);
			
    return sqrt(Dx*Dx + Dy*Dy + Dz*Dz);
  }
  */

  static void getVector(const Atom &a1, const Atom a2, vector<double>& ovec)
  { 
    double Dx, Dy, Dz;
    Dx = (a1.px - a2.px);
    Dy = (a1.py - a2.py);
    Dz = (a1.pz - a2.pz);

    ovec[0] = Dx;
    ovec[1] = Dy;
    ovec[2] = Dz; //{Dx, Dy, Dz};
    //return to_return;
  }
};

//#endif
