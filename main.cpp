#include <iostream>
#include "Graph.h"



int main() {
    Graph<int, int, int> graph;

    cout << boolalpha << graph.empty() << "\n";

    graph[1];

    cout << boolalpha << graph.empty() << "\n";


    return 0;
}
