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

//Lattice.h
//contains code for the Lattice type (which defines the lattice vectors for a crystal
#pragma once

#include "header.h"

using namespace std;

struct Lattice
{
  //moving forward the vec element is not supported. instead, all
  //information is stored only in the mat element.

  vector<double> vec; //stores a,b,c alpha,beta,gamma (in rads)
  //a, b, c > 0 but the angles can be negative but highly not recommended
  //also, it's best if the angles agree with c3 > 0, i.e. defined in the first 4 octants
  vector< vector<double> > mat; //stores vec(a), vec(b), vec(c), always vec(a) = (a,0,0), vec(b) = (b1, b2, 0) and vec(c) = (c1,c2,c3) with c3 > 0;
  //even if you 'try' and set this differently, the setLattice(mat) automatically converts to this form
  
public:
  Lattice(const Lattice& ilat);
  Lattice(const vector<double>& ivec = vector<double>(6,0.0));
  Lattice(const vector< vector<double> > &imat);

  ~Lattice();
  //static const vector<double> DEFAULT_VECTOR; // = vector<double>(6,0.0);

  vector<double> getVector();
  vector< vector<double> > getMatrix();
  
  void setLattice(const vector<double> &ilat);
  void setLattice(const vector< vector<double> > &imat);
};
