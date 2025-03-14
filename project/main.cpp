#include <iostream>
#include <fstream>
#include <cstring>
#include "Digraph.h" 

int main(int argc, char *argv[]) {
    // std::cout << argc << '\n';
    char fileName[32];
    if (argc < 2) {
        std::cout << "Enter filename: ";
        std::cin >> fileName;
    } else 
        strcpy(fileName, argv[1]); //In the process of getting this to work
    // std::cout << argv[1] << '\n';    

    std::ifstream fin(fileName);
    Digraph digraph(fin);
    digraph.print();

    return 0;
}
