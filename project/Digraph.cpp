#include "Digraph.h"
// #include "Queue.h" //For BFS

Node::Node(int _data) : data(_data) {}
Node::Node() : data(0) {}

Digraph::Digraph(std::ifstream &fin) { //Populate the adjacency list from the file stream
    int n = 0, i = 0;

    fin >> n; //We can't differentiate between 0 and -0 so we just assume we start on a new line
    AdjacencyList.Push(); //Add a new list for adjacent nodes
    AdjacencyList.Front().Push(Node(-n)); //Add the node that the list is in comparison to

    while (fin >> n) {
        if (n < 0) {//new line
            AdjacencyList.Push();
            AdjacencyList.Front().Push(Node(-n)); //We denote new lines with a negative sign. Flip the sign again to store
        } else {
            AdjacencyList.Front().Push(Node(n));
        }
    }
}

Digraph::~Digraph() {};

void Digraph::print() {
    for (int i = 0; i < AdjacencyList.getSize(); i++) {
        for (int j = 0; j < AdjacencyList[i].getSize(); j++)
            std::cout << AdjacencyList[i][j].data << (j == 0 ? ": " : " ");
        std::cout << '\n';
    }
}
