#include <stack>
#include <list>
#include <vector>

using std::list;
using std::vector;

class Graph {
    long v;
    vector<list<long> > adj;
    vector<bool> visited;
    
public:
    Graph(long v);
    addEdge(long v, long h);
};

Graph::Graph(long v) {
    this->v = v;
    adj = new vector<list<long> >[v + 1];
    visited = new vector<bool>[v + 1];
}

void Graph::addEdge(long v, long h) {
    adj[v].push_back(h);
}

// 875714 vertices
int main() {
    // input a list of directed edges
    Graph graph(875714);
    long x; // input variable store
    long v; // vertex
    long h; // head
    int seq = 0;     // tracking signal variable for vertex or head component
    while (cin >> x) {
        if (seq == 0) {
            v = x;
            ++seq;
        }
        if (seq == 1) {
            h = x;
            graph.addEdge(v, h);
            --seq;
        }
    }
}