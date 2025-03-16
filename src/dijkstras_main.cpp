#include "dijkstras.h"

int main() {
    Graph G;
    try {
        
        file_to_graph("src/medium.txt", G);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }

    vector<int> previous(G.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(G, 0, previous); 

    for (int destination = 0; destination < G.numVertices; ++destination) {
        vector<int> path = extract_shortest_path(distances, previous, destination);
        int total_cost = distances[destination];
        print_path(path, total_cost);
    }

    return 0;
}