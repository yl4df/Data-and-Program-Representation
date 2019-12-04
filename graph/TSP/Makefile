#Yunlu Li, yl4df, 2019-12-01, Makefile

# Defines the C++ compiler we'll be using
CXX	= clang++ 

# Defines the flags we'll be passing to the C++ compiler
CXXFLAGS	=-std=c++11 

# All of the .o files for our program
OFILES	= middleearth.o traveling.o

# This tells make to create a .o file from a .cpp file, using the
# defaults above (i.e. the CXX and CXXFLAGS macros)
.SUFFIXES: .o .cpp


# How to compile our final program.  Note that we do NOT specify an
# output executable name -- in order for this to work with the grading
# system, the file needs to be a.out (a.exe in Cygwin).
main:	$(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES)
	doxygen
# This will clean up (remove) all our object files.  The -f option
# tells rm to forcily remove the files (i.e. don't ask if they should
# be removed or not).  This removes object files (*.o) and Emacs
# backup files (*~)
clean:
	/bin/rm -f *.o *~

middleearth.o: middleearth.cpp middleearth.h
traveling.o: traveling.cpp middleearth.h

