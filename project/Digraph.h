#ifndef DIGRAPH_H
#define DIGRAPH_H

#include "ResizingArray.h" //For adjacency list
#include <fstream>
#include <iostream>

struct Node { //Should this be in its own file?
    Node(int _data);
    Node();
    int data;
};

class Digraph {
public:
    Digraph(std::ifstream &fin);
    ~Digraph();

    void print();
    
private:
    int N;
    ResizingArray<ResizingArray<Node>> AdjacencyList;
    
};

#endif