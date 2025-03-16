#include "dijkstras.h"

//Your program should print the path from the start vertex (0) to every other node (from 0 to N-1), along with the cost.
int main() {
    Graph G;
    file_to_graph("small.txt", G);

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    int destination = 4;
    vector<int> path = extract_shortest_path(distances, previous, destination);
    print_path(path, distances[destination]);

    return 0;
}