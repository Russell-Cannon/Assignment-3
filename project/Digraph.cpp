#include "Digraph.h"
// #include "Queue.h" //For BFS

Node::Node(int _data) : data(_data) {}
Node::Node() : data(0) {}

Digraph::Digraph(std::ifstream &fin) { //Populate the adjacency list from the file stream
    //Currently, the input is structured kind of funny. 
    //The first number in input is the number of elements. 
    //Then there is an index for each element in graph.
    //Within the same line for each element, their adjacent nodes are listed by index
    //Each list of adjacenct nodes is capped with a -1 to deliminate.

    fin >> N; //Get number of elements
    AdjacencyList = new ResizingArray<Node>[N]; //Array of resizing arrays

    int n = 0, i = 0;
    while (!fin.eof()) {
        fin >> i;
        for (fin >> n; n != -1; fin >> n) { //Read each integer until we get a '-1'
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
