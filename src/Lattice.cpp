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
   Lattice.cpp
   coded by David Miller
   mill2723 at msu dot edu
   
   Contains code for the Lattice class which 
   defines the lattice vectors for a crystal.
***********************************************/
#include "dec.h"

Lattice::Lattice(const Lattice &ilat)
{
  vec = ilat.vec;
  mat = ilat.mat;
}

Lattice::Lattice(const vector<double> &ivec)
{
  this->setLattice(ivec);
}
Lattice::Lattice(const vector< vector<double> > &imat)
{
  this->setLattice(imat);
}

Lattice::~Lattice()
{

}

vector<double> Lattice::getVector()
{
  return vec;
}
vector< vector<double> > Lattice::getMatrix()
{
  return mat;
}
  
void Lattice::setLattice(const vector<double> &ivec)
{
  //cout << "Setting lattice with vector of size: " << ivec.size() << endl;
  if (ivec.size() != 6)
    {
      cerr << "Incorrect lattice vector size." << endl;
      return;
    }
  vec = vector<double>(ivec);
  for (unsigned i = 0; i < 3; i++)
    {
      if (vec[i] < 0) vec[i] *= -1.0; //vec[i] = abs(vec[i]);
    }  
  //cout << "Vector size: " << vec.size() << endl;
  mat = vector< vector<double> >(3, vector<double>(3,0.0));
  //a = (a,0,0)
  //b = (b*cos(gamma),b*sin(gamma),0)
  //c = (c1*cos(beta),c*[cos(alpha)-cos(beta)*cos(gamma)]/sin(gamma),c*sqrt[sin^2(gamma)-cos^2(alpha)-cos^2(beta)+2*cos(alpha)*cos(beta)*cos(gamma)]/sin(gamma))
  //SEE: W. Setyawan and S. Curtarolo, “High-throughput electronic band structure calculations: Challenges and tools,” Comput. Mater. Sci., vol. 49, no. 2, pp. 299–312, 2010.

  //here a,b,c are vec[0,1,2] and alpha,beta,gamma are vec[3,4,5]

  mat[0][0] = vec[0];
  
  //b*cos(gamma)
  mat[1][0] = vec[1] * cos(vec[5]);

  //b*sin(gamma)
  mat[1][1] = vec[1] * sin(vec[5]);

  //c*cos(beta)
  mat[2][0] = vec[2] * cos(vec[4]);

  //c*[cos(alpha)-cos(beta)*cos(gamma)]/sin(gamma)
  mat[2][1] = vec[2] * ( cos(vec[3]) - cos(vec[4])*cos(vec[5]) ) / sin(vec[5]);
  
  //c*sqrt[sin^2(gamma)-cos^2(alpha)-cos^2(beta)+2*cos(alpha)*cos(beta)*cos(gamma)]/sin(gamma)
  mat[2][2] = vec[2] * sqrt(sin(vec[5])*sin(vec[5])-cos(vec[3])*cos(vec[3])-cos(vec[4])*cos(vec[4])+2*cos(vec[3])*cos(vec[4])*cos(vec[5]))/sin(vec[5]);

  for (unsigned i = 0; i < 3; i++)
    {
      for (unsigned j = 0; j < 3; j++)
  	{
  	  if (abs(mat[i][j]) < EPS) mat[i][j] = 0.0;
  	  cout << "Matrix(" << i << "," << j << "): " << mat[i][j] << endl;
  	}
    }

}
void Lattice::setLattice(const vector< vector<double> > &imat)
{
  if (imat.size() != 3)
    {
      cerr << "Incorrect lattice matrix size." << endl;
      return;
    } 
  for (unsigned i = 0; i < 3; i++)
    {
      if (imat[i].size() != 3)
	{
	  cerr << "Incorrect lattice matrix size." << endl;
	  return;
	}
    }
  vector<double> tvec(6);
  for (unsigned i = 0; i < 3; i++)
    {
      tvec[i] = Vector::Norm(imat[i]);
    }
  tvec[3] = Vector::Angle(imat[0],imat[2]);
  tvec[4] = Vector::Angle(imat[1],imat[2]);
  tvec[5] = Vector::Angle(imat[0],imat[1]);


  //*
   for (unsigned i = 0; i < 6; i++)
     {
       cout << "Vector(" << i << "): " << tvec[i] << endl;
    }
   //*/
  this->setLattice(tvec);
}
