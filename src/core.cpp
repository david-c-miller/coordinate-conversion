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

/* *****************************************************
   core.cpp
   coded by David Miller
   mill2723 at msu dot edu

   Contains the core operations of the combined programs 
   here. All of the files that contain a int main(...) 
   call this to handle there operations.

********************************************************/
#include "header.h"
#include "dec.h"

int handle_core_ops(unsigned argc, char* argv[], const Handle& op_handle)
{
  // cout << "Handling operations with Handle class." << endl;

  int to_return;
  
  ifstream infile;
  ofstream outfile;

  istream* ist = &cin;
  ostream* ost = &cout;

  bool\
    BRAVAIS = false,\
    COPY = false,   \
    FORCE = false,\
    HELP = false,\
    MANUAL = false,\
    VERSION = false,\
    NORMALIZE = false,\
    UNIT = false,\
    READ = false,\
    WRITE = false,\
    LAYERED = false;

  //temporary variables
  vector<string> args(argc-1);
  string examine;
  stringstream sbuf;
  int norm_index;
  
  Structure syst = Structure();
  
  if (argc < 1)
    {
      cerr << "Unknown error." << endl;
      return 100;
    }
  if (argc == 1)
    {
      printUsage(op_handle.Name);
      return 0;
    }

  //  for (unsigned i = 0; i < argc; i++)
  //   {
  //   cout << "argv[" << i << "]: " << argv[i] << endl;
  //   }

  if (argc > 1)
    {
      for (unsigned i = 1; i < argc; i++)
	{
	  args[i-1] = string(argv[i]);
	}
      //checks what options are present
      for (unsigned i = 0; i < (argc - 1); i++)
	{
	  examine = string(args[i]);
	  //  cout << "Current string: " << examine << endl;
	  // if (args[i].size() > 1) cout << "Char 0: " << args[i][0] << "\tChar 1: " << args[i][1] << endl;
	  //an option is present
	  if (args[i][0] == '-')
	    {
	      //formal option;
	      if (args[i][1] == '-')
		{
		  examine = args[i].erase(0,2);
		  //  cout << "Modified string: " << examine << endl;
		  if (examine.compare("bravais") == 0) BRAVAIS = true;
		  if (examine.compare("copy") == 0) COPY = true;
		  if (examine.compare("force") == 0) FORCE = true;
		  if (examine.compare("help") == 0) HELP = true;
		  if (examine.compare("layered") == 0) LAYERED = true;
		  if (examine.compare("input") == 0)
		    {
		      if (i == (argc - 1))
			{
			  cerr << "Input option must be followed by a filename." << endl;
			  return -1;
			}
		      infile.open(args[i+1].c_str());
		      ist = &infile;
		      READ = true;
		    }
		  if (examine.compare("manual") == 0) MANUAL = true;
		  if (examine.compare("shift") == 0)
		    {		    
		      if (i == (argc - 1))
			{
			  cerr << "Normalize option must be followed by an index." << endl;
			  return 10;
			}
		      sbuf.str(args[i+1]);
		      sbuf >> norm_index;
		      sbuf.clear();
		      NORMALIZE = true;
		    }
		  if (examine.compare("output") == 0)
		    {		    
		      if (i == (argc - 1))
			{
			  cerr << "Output option must be followed by a filename." << endl;
			  return 10;
			}
		      outfile.open(args[i+1].c_str());
		      ost = &outfile;
		      WRITE = true;
		    }
		  if (examine.compare("version") == 0) VERSION = true;
		  if (examine.compare("unit") == 0) UNIT = true;
		}
	      else
		{
  		  if (args[i].find('b') != string::npos) BRAVAIS = true;
		  if (args[i].find('c') != string::npos) COPY = true;
		  if (args[i].find('f') != string::npos) FORCE = true;
		  if (args[i].find('h') != string::npos) HELP = true;
		  if (args[i].find('m') != string::npos) MANUAL = true;
		  if (args[i].find('v') != string::npos) VERSION = true;
		  if (args[i].find('u') != string::npos) UNIT = true;
		  if (args[i].find('l') != string::npos) LAYERED = true;

		  /*
		    if (args[i].find('i') != string::npos)
		    { 
		    if (args[i].find('o') != string::npos)
		    {
		    cerr << "Cannot specify output and input at the same time." << endl;
		    return -1;
		    }
		    if (i == (argc - 1))
		    {
		    cerr << "Input option must be followed by a filename." << endl;
		    return -1;
		    }
		    infile.open(args[i+1]);
		    READ = true;
		    } 
		    if (args[i].find('o') != string::npos) 
		    {
		    if (args[i].find('i') != string::npos)
		    {
		    cerr << "Cannot specify output and input at the same time." << endl;
		    return -1;
		    }
		    if (i == (argc - 1))
		    {
		    cerr << "Output option must be followed by a filename." << endl;
		    return -1;
		    }
		    outfile.open(args[i+1]);
		    WRITE = true;
		    }
		  */
		}
	    }
	} // end of for loop on args
    } //end of if argc > 1 

  if (VERSION)
    {
      cout << version(version_major, version_minor, version_rev);
      return 0;
    }
  if (HELP)
    {
      printUsage(op_handle.Name);
      return 0;
    }
  if (FORCE)
    {
      cout << "The force option is not enabled at this time.\n";
      cout << "Proceeding without it...\n" << endl;
    }
  if (MANUAL && READ)
    {
      cout << "Cannot read from stdin and from file.\n";
      cout << "Reading from file...\n" << endl;
    }

  if (!(MANUAL || READ))
    {
      cout << "Some form of input is required. To use stdin for input please specify the manual option (--manual or -m)\n" << endl;
      return 10;
    }
  op_handle.Read(syst, *ist);

  if (READ) cout << "Reading from file..." << endl;
  else cout << "Reading..." << endl;
  
  if (NORMALIZE)
    {
      cout << "Will normalize to atom: " << norm_index << endl;
      formatShift(syst, static_cast<unsigned>(abs(norm_index)));
    }

  if (UNIT)
    {
      cout << "Will output atoms as positioned in unit cell." << endl;
      formatUnit(syst);
    }
  if (LAYERED)
    {
      cout << "Will output cell optimized for layered materials." << endl;
      formatLayered(syst);
    }
  if (BRAVAIS)
    {
      cout << "Formatting lattice as a standard Bravais lattice." << endl;
      formatLattice(syst);
    }

  to_return = op_handle.Write(syst, *ost);
  
  //this will later handle the force operation
  //  if (FORCE) 

  if (COPY)
    {
      to_return += op_handle.Write(syst, cout);
    }

  if (READ)
    {
      infile.close();
    }
  if (WRITE)
    {
      outfile.close();
    }

  return to_return;
} //handle_core_ops(...)

string version(int major, int minor, int rev)
{
  stringstream sbuf;
  sbuf << "Version " << major << "." << minor << "." << rev << endl;
  return sbuf.str();
}

void printUsage(string binName)
{
  int val1 = 25, val2 = 15; //unused value val3 = 10;
  //clean this up
  cout << left;
  cout << "Usage: " << binName << " [options...] -input (file) [-output (file)]" << endl;
  cout << endl;
  cout << "Options: " << endl;

  cout << setw(val1) << "--bravais"           << setw(val2) << "-b"            << ": Format the lattice as a standard Bravais lattice." << endl;
  cout << setw(val1) << "--copy"              << setw(val2) << "-c"            << ": Always writes output to stdout." << endl;
  cout << setw(val1) << "--force"             << setw(val2) << "-f"            << ": Forces output regardless of lattice vectors." << endl; 
  cout << setw(val1) << "--help"              << setw(val2) <<  "-h"           << ": Display this screen." << endl;
  cout << setw(val1) << "--input (filename)"  << setw(val2) << "-i (filename)" << ": Reads input from file (filename)." << endl;
  cout << setw(val1) << "--layered"           << setw(val2) << "-l"            << ": Outputs cell optimized for layered materials (-0.5 < w < 0.5)." << endl;
  cout << setw(val1) << "--manual"            << setw(val2) << "-m"            << ": Overrides the need for an input file." << endl;
  cout << setw(val1) << "--shift (n)"         << setw(val2) << "-s (n)"        << ": Normalize the output to atom n (zero indexed)." << endl;
  cout << setw(val1) << "--output (filename)" << setw(val2) << "-o (filename)" << ": Writes output to file (filename)." << endl;
  cout << setw(val1) << "--unit"              << setw(val2) << "-u"            << ": Writes all atoms in the first unit cell." << endl;
  cout << setw(val1) << "--version"           << setw(val2) << "-v"            << ": Prints version info." << endl;
}
