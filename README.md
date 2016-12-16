# Atomic Coordinate File Conversion

Code written by David C. Miller (`mill2723 at msu dot edu`)

Michigan State University

Department of Physics and Astronomy

## Quick Install
 
Try the following:
+ change INSTALLDIR (typically a folder in PATH like
/usr/local/bin)
+ `make install`
  - this will run `make reset`, `make all`, and then install
  the files in the INSTALLDIR

Other options:
+ make final
  - final binaries will be in `./bin`
+ make link
  - will create symbolic links in INSTALLDIR for the binaries
+ make all
  - will make debugging binaries (for distributed versions 
  there is a chance that `make all` runs `make final` and
  `make debug` runs this case)
+ make uninstall
  - removes binaries from INSTALLDIR (whether linked or 
  copied)

You may need to run any of the above as root depending on 
local folder priveleges.

## Information

### Description

This project is for conversion of different coordinate formats
to other useful formats. Typically, any format that can easily
be read and written will have a conversion forwards and backwards
between other other formats. Some formats only have forwards or
backwards versions (that is they cannot be read or cannot be
written).

### Supported File Formats

The currently supported are given below along with their read
and write capacity along with the use of lattice vectors.
L = Lattice vector required, O = Optional, N = Not supported.

- VASP (Vienna ab initio simulation package)................RWL
- XYZ (XYZ format described more in source files)...........RWN
- SIESTA fdf (with species and coordinate info).............-WO
- COORD (A human readable format with lattice info).........RWL

Formats that should be supported in the future:

- XV (SIESTA output format).................................RWL
- FE (facet edge format for Ken Brakke's Surface Evolver)...-WN
- PDB (protein database format).............................RW?

Formats that are in consideration:

- STL (output only)
- LAMMPS input format (I do not know much about this)
- CASTEP input format (or this, but I know that it is a popular software)
- Quantum Espresso format
 
### Test Sets

These currently do not exist but hopefully will in the future.
Tests are implemented to verify that each conversion process
does the following:

	(a) Conserves the desired precision (typically 1E-6)
	
	(b) Conserved lattice parameters in the desired crysallographic
	    format (a = [a 0 0], b = [b1 b2 0], c = [c1 c2 c3])
	    as well as maintaining proper angles.

	(c) All internal crystal operations are performed properly.
	    These include: normalizing to unit cell, shift of coordinates
	    for a specific atom. 

	(d) Acceptable file formats can be returned to the original 
	    format without loss of information (assuming proper format
	    of the input file).

### Bugs

Please report bugs to me (`mill2723 at msu dot edu`) with the subject
"Coordinate Conversion - Bug" and a description of the relevant information
about how to replicate the bug. Please include: the program being run,
version information, an attached input and output file (if possible),
the results of stdout and stderr, and a description of what you expected. 

I will try to take a look at it as soon as possible and get back to
you with a fix or a patch.

### Compiling and Installing

This program was designed to be compiled with the GNU C++ Compiler
(g++) and GNU Make. It also uses some simple bash commands. It *should*
work on any Linux/UNIX system that can meet these requirements but I can
offer no guarentees. I suspect (but have not tested) that this could be
compiled on Cygwin if one so desired.

Currently I have used this on Ubuntu 16.04.

Dependencies:

+ GNU g++ 4.6.4 (although I suspect you could use an earlier version and
be fine)
+ GNU Make 4.0 (again, this is what I have run it with but I suspect
it would work with an earlier version)
+ GNU bash 4.3.30 (same as above)

Also, this does compile with the C++98 ISO standards (using the -ansi
tag in g++). This is to potentially improve portability since
I assume that most compilers support this standard (although you will
need to change the compiler options).

Also, the code was written on an x64 system but there should not be many
dependencies if any. If you do compile and run this code (completing the
tests properly) on a widely different system than what has been described
(or perhaps just a very popular system) please let me know so I can add it
to this document.

To install:

(a) Modify the Makefile to match your desired settings. This
may include changing the compiler, flags, install
directory, or programs to be compiled. Again, I can make
no guareentees about the operation of the program
without using the default settings on a system that it
has been tested on.

(b) Run `make`

(c) Assuming everything went smoothly run `make install`
(you may need to run this as root or use sudo depending on
the installation directory). I was also verify that there
is nothing in the install directory with an identical name
to one of the binaries being added. The makefile *will*
overwrite it.

- To uninstall simply run `make uninstall`
- The install script only makes a link from the binary
directory to the bin/ directory for the local compilation.
Thus, if you recompile, there is no need to
reinstall.

Other: `make clean` will delete any extraneous files.
`make reset` will delete the binary files.

### Modification

All code included here was written by myself (unless you have 
received a modify version at which point I would request the 
modifier to also add their contact information and a brief
description of the modification. This project should also be
available at github at

<https://github.com/david-c-miller/coordinate-conversion.git>

The best place to get a change log (unless you already have one)
is from the git repository. Otherwise, there is currently no
official channel for one and likely will not be anytime soon.

### Disclaimer

I wrote this to be a useful program for computational work
with crystallographic coordinates or other molecular/atomic
systems. I take no responsibility for it. I would reccommend
that any use of this is hand verified (at least look at the result
in a viewer to see if it looks ok). Also, for use with DFT such
as VASP or SIESTA I would reccomend that you use this prior to
relaxation of the ionic sites and electronic calculations.

## License

This code is licensed under the Apache 2.0 License. See LICENSE
for details.