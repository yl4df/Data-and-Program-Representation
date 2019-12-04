#Yunlu Li, yl4df, 2019-11-23, Makefile

CXX=clang++ $(CXXFLAGS)
CXXFLAGS=-std=c++11
ENCFILES= heap.o huffmanenc.o node.o
DECFILES= heap.o huffmandec.o node.o


.SUFFIXES: .o .cpp

all: encoder decoder

encoder: $(ENCFILES)
	$(CXX)  $(ENCFILES) -o encoder
decoder: $(DECFILES)
	$(CXX)  $(DECFILES) -o decoder

clean:
	-rm -f *.o *~ a.out

node.o: node.cpp node.h
heap.o: heap.cpp heap.h node.h
huffmanenc.o: huffmanenc.cpp heap.h node.h
huffmandec.o: huffmandec.cpp heap.h node.h
