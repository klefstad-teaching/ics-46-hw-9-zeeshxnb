#include "dijkstras.h"
struct Node {
    int vertex;
    int cost;
    Node(int v, int c) : vertex(v), cost(c) {}
};

struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.cost > b.cost;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> dist(n, INF);
    previous.assign(n, -1);

    priority_queue<Node, vector<Node>, Compare> pq;
    dist[source] = 0;
    pq.push(Node(source, 0));
    vector<bool> visited(n, false);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if (visited[u]) continue;
        visited[u] = true;
        for (auto &edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;
            if (!visited[v] && dist[u] != INF && (dist[u] + w < dist[v])) {
                dist[v] = dist[u] + w;
                previous[v] = u;
                pq.push(Node(v, dist[v]));
            }
        }
    }
    return dist;
}

vector<int> extract_shortest_path(const vector<int>&, const vector<int>& previous, int destination) {
    vector<int> pth;
    int curr = destination;
    while (curr != -1) {
        pth.push_back(curr);
        curr = previous[curr];
    }
    reverse(pth.begin(), pth.end());
    return pth;
}

void print_path(const vector<int>& path, int total) {
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;

    cout << "Total cost is " << total << endl;
}
