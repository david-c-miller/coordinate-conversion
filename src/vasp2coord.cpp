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

/* ****************************************
   vasp2coord.cpp
   coded by David Miller
   mill2723 at msu dot edu
******************************************/

#include "dec.h"

using namespace std;

int main(int argc, char* argv[])
{
  Handle h = Handle(Default::vaspcoord);
  return handle_core_ops(static_cast<unsigned>(argc), argv, h);
}
