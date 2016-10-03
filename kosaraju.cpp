// kosaraju.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// code structure from http://www.geeksforgeeks.org/strongly-connected-components/

#include <stack>
#include <list>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

using std::list;    using std::cin;     using std::cout;    using std::sort;
using std::vector;  using std::map;     using std::endl;    using std::stack;

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
	void printList();
	void printF();
	void flipF();

public:
	Graph(long);
	long *f;
	long *fbase;
	void addEdge(long, long);
	vector<long> getLeaders();
};

Graph::Graph(long v) {  // constructor
	this->v = v;  // set the number of vertices
	adj = new list<long>[v + 1];    // set size to v + 1 due to not using index 0
	explored = new bool[v + 1];     // keep track of explored nodes
	f = new long[v + 1];            // initialize the node labeling
	fbase = new long[v + 1];
	for (long i = 0; i != v + 1; ++i) {
		f[i] = i;
	}
	for (long i = 0; i != v + 1; ++i) {
		fbase[i] = i;
	}
	this->setUnexplored();
	leader = new long[v + 1];
}

void Graph::addEdge(long v, long h) {
	adj[v].push_back(h);    // pushes the head onto the list corresponding to v
}

Graph Graph::reverse() {
	Graph g(v);     // initializes the new reversed graph
	for (long i = 1; i != v + 1; ++i) { // every node
		for (listit it = this->adj[i].begin(); it != this->adj[i].end(); ++it) { // every head
			g.addEdge(*it, i);  // reverses the arc
		}
	}
	return g;
}

void Graph::setUnexplored() {
	for (long i = 0; i != v + 1; ++i) {
		explored[i] = false;    // set all explored values to false
	}
}

void Graph::DFSLoop(int run) {
	t = 0;  // initialize timing variable
	s = -1; // source initialized to non existent -1

	for (long i = v; i != 0; --i) {
//		     cout << "DFSLoop iteration i = " << i << " and f[i] = " << fbase[i] << " for run " << run << endl;
		if (explored[fbase[i]] == false) { // checks if the node according to f is explored
			s = fbase[i]; // sets that node to be the source
			DFS(fbase[i], run);
		}
	}
}

void Graph::DFS(long i, int run) {
	explored[i] = true;  /// HERE? IS THIS RIGHT? NEED TO FIGURE OUT INDICES
	if (run == 2) leader[i] = s; // second run only

								 /*
								 stack<long> stack;
								 stack.push(i);
								 listit it;

								 while (!stack.empty()) {
								 cout << "while loop iteration" << endl;
								 s = stack.top();
								 stack.pop();
								 for (it = adj[s].begin(); it != adj[s].end(); ++it) {
								 if (explored[*it] == false) {
								 explored[*it] == true;
								 stack.push(*it);
								 }
								 }
								 ++t;
								 if (run == 1) f[i] = t; // first run only
								 }

								 */


	for (listit it = this->adj[i].begin(); it != this->adj[i].end(); ++it) {
		if (explored[*it] == false) {
			if (i == 874931) cout << "it* = " << *it << endl;
			DFS(*it, run);
		}
	}
	++t;
	if (run == 1) f[i] = t; // first run only

}

void Graph::printList() {
	cout << "Printing the adjacency list: " << endl;
	for (long i = 1; i != v + 1; ++i) { // every node
		cout << "Node " << i << ": ";
		for (listit it = this->adj[i].begin(); it != this->adj[i].end(); ++it) { // every head
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Graph::printF() {
	cout << "Printing f(i): ";
	for (long i = 1; i != v + 1; ++i) {
		cout << f[i] << " ";
	}
	cout << endl << endl;
}

void Graph::flipF() {
	long *work = new long[v + 1];
	for (long i = 0; i != v + 1; ++i) {
		work[fbase[i]] = i;
	}
	for (long i = 0; i != v + 1; ++i) {
		fbase[i] = work[i];
	}
}

vector<long> Graph::getLeaders() {
	Graph revG = this->reverse();
	revG.setUnexplored();
	cout << "Reversal complete." << endl;
	revG.DFSLoop(1);
	cout << "DFSLoop on Grev complete." << endl;
	this->fbase = revG.f; // copies the pointer, not a new array
	this->setUnexplored();
	this->flipF();
	this->DFSLoop(2);
	cout << "DFSLoop on G complete." << endl;
	vector<long> leader_vec;
	for (long i = 1; i != v + 1; ++i) {
		leader_vec.push_back(this->leader[i]);
	}
	map <long, long> SCC;
	for (vector<long>::iterator it = leader_vec.begin(); it != leader_vec.end(); ++it) {
		++SCC[*it];
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
		else if (seq == 1) {
			h = x;
			//            if (v <= 400000 && h <= 400000) 
			graph.addEdge(v, h);
			//            cout << "Added " << v << " and " << h << endl;
			--seq;
		}
	}
	cout << "File input complete." << endl;
	vector<long> SCC = graph.getLeaders();
	sort(SCC.rbegin(), SCC.rend());
	for (vector<long>::iterator it = SCC.begin(); it != SCC.begin() + 5; ++it) {
		cout << "SCC size: " << *it << endl;
	}

}
