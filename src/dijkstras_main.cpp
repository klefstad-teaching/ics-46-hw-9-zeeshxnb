#include "dijkstras.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "usage: " << argv[0] << " <graph_file>" << endl;
        return 1;
    }
    string filename = argv[1];
    Graph G;
    try {
        file_to_graph(filename, G);
    } catch (const exception &e) {
        cerr << "error reading graph: " << e.what() << endl;
        return 1;
    }
    int source = 0;
    vector<int> previous; 
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    for (int v = 0; v < G.numVertices; v++) {
        vector<int> path = extract_shortest_path(distances, previous, v);
        print_path(path, distances[v]);
    }
    return 0;
}
