#include "Digraph.h"

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

ResizingArray<int>* Digraph::BFS(int start, int target){
    //handles edge case where start is the same as target
    if (start == target) {
        std::cout << "Shortest path from " << start << " to " << target << ": " << start << std::endl;
        return nullptr;
    }

    Queue<int> q;
    ResizingArray<bool> visited;
    ResizingArray<int> previous;
    
    visited = ResizingArray<bool>();
    previous = ResizingArray<int>();

    //Initializes the visited and previous Resizing Arrays
    for (int i = 0; i < AdjacencyList.getSize(); i++) {
        visited.Push(false);
        previous.Push(-1);  //-1 means no predecessor
    }

    //Start BFS
    q.Push(start);
    visited[start] = true;

    while (!q.IsEmpty()) {
        //Pops the node at the front of the queue
        int node = q.Pop();

        //If target node is reached, reconstruct the path
        if (node == target)
        {
            //Reconstruct path using a ResizingArray
            ResizingArray<int> path;
            for (int v = target; v != -1; v = previous[v]) {
                path.Push(v);
            }

            // Reverse the path to get the correct order
            ResizingArray<int>* correctPath = new ResizingArray<int>;
            for (int i = path.getSize() - 1; i >= 0; --i) {
                correctPath->Push(path[i]);
            }
            return correctPath;
        }

        //Traverses neighbors of the current node directly
        for (int j = 0; j < AdjacencyList[node].getSize(); j++) {
            int neighbor = AdjacencyList[node][j].data;
            
            if (!visited[neighbor]) {
                q.Push(neighbor);
                visited[neighbor] = true;
                previous[neighbor] = node;  //Marks the predecessor
            }
        }
    }

    return nullptr;
}

int Digraph::getSize() {
    return AdjacencyList.getSize();
}
