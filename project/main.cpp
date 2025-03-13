// #include <iostream>
#include <fstream>
// #include <cstring>
#include "Digraph.h" 

int main(int argc, char *argv[]) {
    char fileName[32] = "input.txt";
    // if (argc == 0)
    //     std::cin >> fileName;
    // else 
    //     strcpy(fileName, argv[0]);

    std::ifstream fin(fileName);
    Digraph digraph(fin);
    digraph.print();

    return 0;
}
