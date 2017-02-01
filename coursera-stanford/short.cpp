#include <list>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>

using std::list;    using std::cin;     using std::cout;    using std::sort;
using std::vector;  using std::map;     using std::endl;    using std::istringstream;
using std::pair;    using std::string;

typedef list<pair<int, long> >::iterator listit;

class Graph {
// variables
	int n; // number of vertices

    list<pair<int, long> >* adj;
    
    long* distance;
    bool* processed;

// methods
    void updateAdjacent(int);

public:
	Graph(int);
    void shortestPath();
	void addEdge(int, int, long);
    void printVertex(int);
    void printDistances();
    void printDistance(int);
    int minDistance();
};

int Graph::minDistance() {
    int result = -1;
    long minDistance = 1000001;
    for (int i = 1; i != n + 1; ++i) {
        if (processed[i] == false && distance[i] < minDistance) {
            minDistance = distance[i];
            result = i;
        }
    }
    return result;
}

void Graph::updateAdjacent(int vertex) {
    for (listit i = adj[vertex].begin(); i != adj[vertex].end(); ++i) {
        if (processed[(*i).first] == false) {
            if (distance[vertex] + (*i).second < distance[(*i).first]) {
                distance[(*i).first] = distance[vertex] + (*i).second;
            }
        }
    }
}

void Graph::printVertex(int s) { // used this to debug file input logic
    cout << "Printing edges connected to vertex " << s << endl;
    for (listit i = adj[s].begin(); i != adj[s].end(); ++i) {
        cout << "Node: " << (*i).first << "\t" << "Distance: " << (*i).second << endl;
    }
}

void Graph::printDistances() {
    for (int i = 1; i != n + 1; ++i) {
        cout << "Distance to vertex " << i << " is " << distance[i] << endl;
    }
    cout << endl;
}

void Graph::printDistance(int i) {
    cout << "Distance to vertex " << i << " is " << distance[i] << endl;
}

void Graph::shortestPath() {
    int closestVertex = minDistance();
    while (closestVertex != -1) {
        processed[closestVertex] = true;
        updateAdjacent(closestVertex);
        closestVertex = minDistance();
    }
}

Graph::Graph(int n) {  // constructor
	this->n = n;  // set the number of vertices

	adj = new list<pair<int, long> >[n + 1];    // set size to v + 1 due to not using index 0

    distance = new long[n + 1];    // keeping track of distances
	processed = new bool[n + 1];     // keep track of explored nodes
    
	for (long i = 0; i != n + 1; ++i) {
		distance[i] = 1000000;  // 1000000 being chosen as equivalent to infinite distance
        processed[i] = false;
	}
    distance[1] = 0;
}

void Graph::addEdge(int source, int head, long distance) {
	adj[source].push_back(std::make_pair(head, distance) );    // pushes the head onto the list corresponding to v
}
// 200 vertices

int main() {
    Graph graph(200);

    long i;
    string s;
    string pair;
    
    for (int z = 0; z != 200; ++z) {
        getline(cin, s, '\n');        // get line as string
        istringstream iss(s);   // convert string to input stream

        iss >> i;               // obtain first number
        int vertex = i;         // to defined the source vertex
        int node;
        long dist;

        int seq = 0;
        while (iss >> i) {      // while line still streams
        
            if (seq == 0) {
//                cout << "Seq 0: " << i << "\t";
                node = i;       // head node
                ++seq;
            }
            else {
//                cout << "Seq 1: " << i << endl;
                dist = i;
//                cout << "Adding vertex, node, dist: " << vertex << ", " << node << ", " << dist << endl;
                graph.addEdge(vertex, node, dist);
                --seq;
            }

            if (iss.peek() == ',') iss.ignore();
        }
    }
    graph.shortestPath();

//    graph.printVertex(150);

//    graph.printDistances();


    graph.printDistance(7);
    graph.printDistance(37);
    graph.printDistance(59);
    graph.printDistance(82);
    graph.printDistance(99);
    graph.printDistance(115);
    graph.printDistance(133);
    graph.printDistance(165);
    graph.printDistance(188);
    graph.printDistance(197);
    
    cout << endl;
}
