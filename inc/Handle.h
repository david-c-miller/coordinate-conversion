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

//Handle.h 

//contains class to pass to handle_core_ops
//this class will contain all the information for reading/writing the files types that the executable wants
//this ensures that future programs can be written that don't have to alter handle_core_ops and only write an int main(int argc, char* argv[]){...} which contains the necessary information to call handle_core_ops(...);
#pragma once

#include "header.h"
#include "Structure.h"

typedef int (*ReadFunction)(Structure&, istream &);
typedef int (*WriteFunction)(Structure&, ostream &);

class Handle
{
 private:
  
  public:
  ReadFunction Read;
  WriteFunction Write;
  string Name;
  string Comments;


  explicit Handle(const ReadFunction& iread, const WriteFunction& iwrtie, const string iname, const string icom = "Handle for read and write operations.");

  Handle(const Handle& ihand);
  ~Handle();
};
