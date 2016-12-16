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

/* ********************************************
   functions.cpp
   coded by David Miller
   mill2723 at msu dot edu

   contains general and not otherwised 
   categorized functions   

**********************************************/

#include "header.h"
#include "dec.h"

using namespace std;

double degtorad(double deg)
{
  return PI*deg/180.0;
}

double radtodeg(double rad)
{
  return 180.0*rad/PI;
}

void calcFracVector(const Lattice& ilat, const vector<double>& icoord, vector<double>& ofrac)
{
  Lattice tmp = Lattice(ilat);
  ofrac = vector<double>(3,0.0);
  vector< vector<double> >mat = tmp.getMatrix();

  ofrac[2] = icoord[2] / mat[2][2];
  ofrac[1] = (icoord[1] - (ofrac[2]*mat[2][1]) ) / mat[1][1];
  ofrac[0] = (icoord[0] - (ofrac[1]*mat[1][0]) - (ofrac[2]*mat[2][0]) ) / mat[0][0];
}

void calcCartVector(const Lattice& ilat, vector<double>& ocoord, const vector<double>& ifrac)
{
  Lattice tmp = Lattice(ilat);
  ocoord = vector<double>(3,0.0);
  vector< vector<double> >mat = tmp.getMatrix();

  ocoord[0] = ifrac[0]*mat[0][0] + ifrac[1]*mat[1][0] + ifrac[2]*mat[2][0];
  ocoord[1] = ifrac[1]*mat[1][1] + ifrac[2]*mat[2][1];
  ocoord[2] = ifrac[2]*mat[2][2];
}

namespace Vector
{
  double Norm(const vector<double> ivec)
  {
    double sum = 0.0;
    for (unsigned i = 0; i < ivec.size(); i++)
      {
	sum += ivec[i] * ivec[i];
      }
    return sqrt(sum);
  }
  double Dot(const vector<double>& ia, const vector<double>& ib)
  {
    if (ia.size() != ib.size())
      {
	cerr << "Vector dot product requires the vectors be the same size." << endl;
	throw -1;
      }
    double sum = 0.0;
    for (unsigned i = 0; i < ia.size(); i++)
      {
	sum += ia[i] * ib[i];
      }
    return sum;
  }
  vector<double> Cross(const vector<double>& ia, const vector<double>& ib)
  {
    if (ia.size() != 3 || ib.size() != 3)
      {
	cerr << "Vector cross product only defined for size = 3." << endl;
	throw -1;
      }
    vector<double> toret(3,0.0);
    
    toret[0] = ia[1]*ib[2] - ia[2]*ib[1];
    toret[1] = ia[2]*ib[0] - ia[0]*ib[2];
    toret[2] = ia[0]*ib[1] - ia[1]*ib[0];

    return toret;
  }

  double Angle(const vector<double>& ia, const vector<double>& ib)
  {
    if (ia.size() != 3 || ib.size() != 3)
      {
	cerr << "Can only find the angle between 3-D vectors." << endl;
	throw -1;
      }
    double dot = Vector::Dot(ia,ib);
    double na = Vector::Norm(ia);
    double nb = Vector::Norm(ib);
    
    double angle = acos(dot/(na*nb));

    return angle;
  }
}
