// code structure from http://www.geeksforgeeks.org/strongly-connected-components/

#include <stack>
#include <list>
#include <vector>
#include <iostream>
#include <map>

using std::list;    using std::cin;     using std::cout;
using std::vector;  using std::map;     using std::endl;

typedef vector<list<long> >::size_type vecsz;
typedef list<long>::iterator listit;

class Graph {
    long t;
    long s;
    long *leader;
    long v;
    list<long> *adj;
    bool *explored;
    

    Graph reverse();
    void setUnexplored();
    void DFSLoop(int);
    void DFS(long, int);
    
public:
    Graph(long);
    long *f;
    void addEdge(long, long);
    vector<long> getLeaders();
};

Graph::Graph(long v) {
    this->v = v;
    adj = new list<long>[v + 1];
    explored = new bool[v + 1];
    f = new long[v + 1];
    for (long i = 0; i != v + 1; ++i) {
        f[i] = i;
    }
}

void Graph::addEdge(long v, long h) {
    adj[v].push_back(h);
}

Graph Graph::reverse() {
    Graph g(v + 1);
    for (long i = 1; i != v + 1; ++i) { // every node
        for (listit it = this->adj[i].begin(); it != this->adj[i].end(); ++it) { // every head
            g.addEdge(*it, i);
        }
    }
    return g;
}

void Graph::setUnexplored() {
    for (long i = 0; i != v + 1; ++i) {
        explored[i] = false;
    }
}

void Graph::DFSLoop(int run) {
    t = 0;
    s = -1;
    if (run == 2) {

    }

    for (long i = v; i != 0; --i) {
        if (run == 2) cout << "Testing program reach in DFSLoop " << i <<endl;
        if (explored[f[i]] == false) {
            s = f[i];
            DFS(f[i], run);
        }
    }
}

void Graph::DFS(long i, int run) {
    explored[i] = true;
    if (run == 2) leader[i] = s; // second run only
    if (run == 2) cout << "Testing program reach in DFS " << i << endl;
    for (listit it = this->adj[i].begin(); it != this->adj[i].end(); ++it) {
        if (explored[*it] == false) {
            DFS(*it, run);
        }
    }
    ++t;
    if (run == 1) f[i] = t; // first run only
}

vector<long> Graph::getLeaders() {
    Graph revG = this->reverse();
    revG.DFSLoop(1);
    this->f = revG.f;
    
    for (long i = 1; i != v + 1; ++i) {
        cout << this->f[i] << " ";
    }
    cout << "Testing program reach. 1" << endl;
    this->setUnexplored();
    this->DFSLoop(2);
    vector<long> leader_vec;
    for(long i = 1; i != v + 1; ++i) {
        leader_vec.push_back(this->leader[i]);
    }

    map <long, long> SCC;

    for (long i = 1; i != v + 1; ++i) {
        ++SCC[leader_vec[i]];
    }

    vector<long> SCC_sizes;

    for (map <long, long>::iterator it = SCC.begin(); it != SCC.end(); ++it) {
        SCC_sizes.push_back(it->second);
    }
    return SCC_sizes;
}

// 875714 vertices
int main() {
    // input a list of directed edges
//    Graph graph(875714);
    Graph graph(9);
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
    cout << "Testing program reach." << endl;
    vector<long> SCC = graph.getLeaders();

    for(vector<long>::iterator it = SCC.begin(); it != SCC.end(); ++it) {
        cout << "SCC size: " << *it << endl;
    }
}