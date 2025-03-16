#include "dijkstras.h"

struct Node {
    int vertex, weight;
    Node(int v, int w) : vertex(v), weight(w) {}
    bool operator>(const Node& other) const { return weight > other.weight; }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    vector<int> distance(n, INF); 
    previous.assign(n, -1)
    vector<bool> visited(n, false); 

    priority_queue<Node, vector<Node>, greater<Node>> pq; 
    pq.push(Node(source, 0));
    distance[source] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.vertex;

        if (visited[u]) {
            continue; 
        }

        visited[u] = true;

        
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

    return distance; 
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;

    if (distances[destination] == INF) {
        return path; 
    }
    
    int current = destination;

    
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }

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


