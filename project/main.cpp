#include <iostream>
#include <fstream>
#include <cstring>
#include "Digraph.h" 

int main(int argc, char *argv[]) {
    char fileName[32];
    if (argc < 2) {
        std::cout << "Enter filename: ";
        std::cin >> fileName;
    } else 
        strcpy(fileName, argv[1]);

    std::ifstream fin(fileName);
    Digraph digraph(fin);
    digraph.print();

    return 0;
}
