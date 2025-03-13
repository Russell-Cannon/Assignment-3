CPP := g++ # change to clang++

main:	main.o Digraph.o
	$(CPP) -o main.exe main.o Digraph.o

main.o:	main.cpp
	$(CPP) -c -o $@ $<

Digraph.o:	Digraph.cpp Digraph.h
	$(CPP) -c -o $@ $<
