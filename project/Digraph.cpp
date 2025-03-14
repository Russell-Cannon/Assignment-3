#include "Digraph.h"
// #include "Queue.h" //For BFS

Node::Node(int _data) : data(_data) {}
Node::Node() : data(0) {}

Digraph::Digraph(std::ifstream &fin) { //Populate the adjacency list from the file stream
    fin >> N;
    AdjacencyList = new ResizingArray<Node>[N]; //Array of resizing arrays

    for (int i = 0; i < N; i++) {
        int count;
        fin >> count;
        for (int j = 0; j < count; j++) {
            int n;
            fin >> n;
            AdjacencyList[i].Push(Node(n));
        }
    }
}

Digraph::~Digraph () {
    delete [] AdjacencyList;
}

void Digraph::print() {
    for (int i = 0; i < N; i++) {
        std::cout << i << ": ";
        for (int j = 0; j < AdjacencyList[i].getSize(); j++)
            std::cout << AdjacencyList[i][j].data << ' ';
        std::cout << '\n';
    }
}
