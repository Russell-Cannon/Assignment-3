#ifndef DIGRAPH_H
#define DIGRAPH_H

#include "ResizingArray.h" //For adjacency list
#include "Queue.h" //For BFS
#include <iostream>
#include <fstream>

struct Node { //Should this be in its own file?
    Node(int _data);
    Node();
    int data;
};

class Digraph {
public:
    Digraph(std::ifstream &fin);
    ~Digraph();
    ResizingArray<int>* BFS(int, int);
    void print();
    int getSize();
    
private:
    int N;
    ResizingArray<ResizingArray<Node>> AdjacencyList;
    
};

#endif