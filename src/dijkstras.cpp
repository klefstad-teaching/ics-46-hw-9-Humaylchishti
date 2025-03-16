#include "dijkstras.h"

struct Node {
    int vertex, weight;
    Node(int v, int w) : vertex(v), weight(w) {}
    bool operator>(const Node& other) const { return weight > other.weight; }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    vector<int> distance(n, INF); // Distance array
    vector<bool> visited(n, false); // Visited array

    priority_queue<Node, vector<Node>, greater<Node>> pq; // Min-heap priority queue
    pq.push(Node(source, 0));
    distance[source] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.vertex;

        if (visited[u]) {
            continue; // Skip if already visited
        }

        visited[u] = true;

        // Explore neighbors of u
        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }

    return distance; // Return the final distances
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    int current = destination;

    // Trace the path from destination to source
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }

    // Manually reverse the path without using the reverse function
    vector<int> reversed_path;
    for (int i = path.size() - 1; i >= 0; --i) {
        reversed_path.push_back(path[i]);
    }

    return reversed_path;
}


void print_path(const vector<int>& path, int total) {
    for (int vertex : path) {
        cout << vertex << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}


