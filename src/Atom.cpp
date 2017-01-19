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

/* ****************************************************
   Atom.cpp
   coded by David Miller
   mill2723 at msu dot edu

   contains definitions of functions for the struct Atom
******************************************************/
#include "Atom.h"

Atom::Atom(const string ielem, const double ix, const double iy, const double iz) :element(ielem), px(ix), py(iy), pz(iz)
{
}

Atom::Atom(const Atom &iatom) : element(iatom.element), px(iatom.px), py(iatom.py), pz(iatom.pz)
{
}

Atom::Atom(const string ielem, const vector<double> ivec) : element(ielem)
{
  if (ivec.size() == 3)
    {
      px = ivec[0]; py = ivec[1]; pz = ivec[2];
    }
  else
    {
      cerr << "Atoms must exist in 3-D space with an x, y, and z component." << endl;
    }
}

Atom::~Atom()
{

}

void Atom::setPosition(vector<double>& ivec)
{
  px = ivec[0]; py = ivec[1]; pz = ivec[2];
}

vector<double> Atom::Position()
{
  vector<double> vec(3);
  vec[0] = px;
  vec[1] = py;
  vec[2] = pz;
  
  return vec;
}

void Atom::setElement(string ielem)
{
  char a, b;
  a = ielem[0];
  if (ielem.size() > 1) b = ielem[1];
  else b = ' ';

  element.clear();
  element.push_back(a);
  if (b != ' ')  element.push_back(b);

}
void Atom::getElement(string oelem)
{
  oelem = this->Element();
}

string Atom::Element()
{
    char a, b;
  a = element[0];
  if (element.size() > 1) b = element[1];
  else b = ' ';

  element.clear();
  element.push_back(a);
  if (b != ' ') element.push_back(b);

  return element; 
}
