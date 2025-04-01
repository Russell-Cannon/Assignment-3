CPP := clang++ # change to clang++ for final submission

main.out:	main.o Digraph.o
	$(CPP) -o main.out main.o Digraph.o

main.o:	main.cpp
	$(CPP) -c -o $@ $<

Digraph.o:	Digraph.cpp Digraph.h
	$(CPP) -c -o $@ $<
