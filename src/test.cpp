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

//test.cpp
//testing for the code:

#include "dec.h"

using namespace std;

int main(int argc, char* argv[])
{
  cout << "Testing..." << endl;
  
  vector<double> one(3);// = vector<double>(3);
  one[0] = 2.0;
  one[1] = 3.0;
  one[2] = 4.0;

  vector<double> two(3);
  two[0] = 0.0;
  two[1] = 0.0;
  two[2] = 5.333333330;
  

  cout << "Norm of one: " << Vector::Norm(one) << endl;
  cout << "Norm of two: " << Vector::Norm(two) << endl;
  cout << "Dot product of one and two: " << Vector::Dot(one,two) << endl;
  cout << "Angle is: " << radtodeg(Vector::Angle(one,two)) << endl;

  Handle vasp_xyz(Read::readVASP, Write::writeXYZ,"vasp2xyz", "Converts a VASP coordinate file to the XYZ (XMol) format with loss of lattice information.");

  Handle test = Handle(Default::vaspcoord);

  return 1;
}
