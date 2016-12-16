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

//vasp2xyz.cpp
//used for converting VASP files to human readable coordinates

#include "dec.h"

using namespace std;

int main(int argc, char* argv[])
{

  Handle h = Handle(Default::vaspxyz);
  return handle_core_ops(static_cast<unsigned>(argc), argv, h);

}

/*
  //for debugging purposes only;
  //fprintf(stdout,"Starting vasp2coord with %d arguments.\n",argc);
  cout << "Test..." << endl;
  cerr << "Error test. No actual error." << endl;
  cout << "Starting vasp2xyz with " << argc << " arguments." << endl;

  int to_return;
  //this gathers the arguments together
  switch (argc) 
    {
    case 0:
      cerr << "Unknown error." << endl; //(stderr,"Unknown Error.\n");
      to_return = 0;
      break;
    case 1:
      printUsage("vasp2xyz");
      to_return = 1;
      break;
    default:
      cout << "General case." << endl;
      to_return = handle_core_ops(static_cast<unsigned>(argc), argv, VASPXYZ);
      break;
    } 
  return to_return;
}
*/
