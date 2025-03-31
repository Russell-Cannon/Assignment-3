#include <iostream>
#include <fstream>
#include <cstring>
#include "Digraph.h" 

int main(int argc, char *argv[]) {
    char fileName[32];
    if (argc < 2) {
        // std::cout << "Enter filename: ";
        // std::cin >> fileName;
        strcpy(fileName, "input.txt");
    } else 
        strcpy(fileName, argv[1]);

    std::ifstream fin(fileName);
    Digraph digraph(fin);
    digraph.print();

    int start, target; // Set target node to whatever you want to test
    std::cin >> start;
    std::cin >> target;
    std::cout << "Finding shortest path from " << start << " to " << target << ":\n";
    digraph.BFS(start, target);

    return 0;
}