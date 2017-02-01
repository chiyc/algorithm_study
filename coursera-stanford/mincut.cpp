#include <map>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <time.h>

using std::list;    using std::cout;    using std::cin;     using std::istringstream;
using std::map;     using std::endl;    using std::string;  using std::domain_error;

int karger(map <int, list<int> > );
void contraction(map <int, list<int> >&);
int nrand(int);
void printnode(map <int, list<int> >&, int);

typedef map <int, list<int> >::iterator mapit;
typedef list<int>::iterator listit;

int main() {
        srand ( time(NULL) );
    map <int, list<int> > adj;
    int i;
    string s;
    for (int z = 0; z != 200; ++z) {
        getline(cin, s);
        istringstream iss(s);
        iss >> i;
        int line = i;
        while (iss >> i) {
            adj[line].push_back(i);
        }
    }
    cout << "Initial map size: " << adj.size() << endl;
    mapit it = adj.begin();
    cout << it->second.front() << endl;
    long cut = karger(adj);
    long mincut = cut;
//        cout << "Cut iteration: " << 1 << "\t" << "Min Cut: " << cut;
//        cout << "\t" << "Node A: " << adj.begin()->first << endl;

    for (unsigned long long i = 0; i != 1000; ++i) {
        cut = karger(adj);
        cout << "Cut iteration: " << i << "\t" << "Min Cut: " << cut;
        cout << "\t" << "Node A: " << adj.begin()->first << endl;
        if (cut < mincut) {
            mincut = cut;
        }
    }
    
    
    cout << "The minimum cut on this run is: " << mincut << endl;
}

int karger(map <int, list<int> > a) {
    int i = 0;
    while (a.size() > 2) {
        contraction(a);
        ++i;
    }
    cout << "Contractions: " << i << endl;
    cout << "Final map size: " << a.size() << endl;
    return a.begin()->second.size();
}

void contraction(map <int, list<int> >& a) {
    

    mapit random_node = a.begin();
    // generate random number out of size of a

 //   cout << "Calling nrand(a.size())" << endl;

    int random_node_select = nrand(a.size());
//    cout << "random_node_select: " << random_node_select << endl;
    for (int i = 0; i != random_node_select; ++i) {
        ++random_node;
    }

    //generate random edge from the list associated with the random node
    listit random_edge = random_node->second.begin();

//    cout << "Calling nrand for edge" << endl;

    int random_edge_select = nrand(random_node->second.size());
//    cout << "random_edge_select: " << random_edge_select << endl;
    for (int i = 0; i != random_edge_select; ++i) {
        ++random_edge;
    }
    int nodea = random_node->first;
    int nodeb = *random_edge;

    
//    cout << "Random node: " << random_node->first << endl;
//    cout << "Random node: " << nodea << endl;
//    cout << "Random edge: " << *random_edge << endl;
//    cout << "Random edge: " << nodeb << endl;


    random_node->second.remove(nodeb); // removes nodea from nodeb connections
    a[nodeb].remove(nodea); // removes node a from node b

    for (listit it = a[nodeb].begin(); it != a[nodeb].end(); ++it) {
        a[*it].remove(nodeb);
        a[*it].push_back(nodea);
    }
    a[nodea].splice(a[nodea].begin(), a[nodeb]); // splices nodeb list onto nodea
    a.erase(nodeb);

//    cout << "Map size following contraction: " << a.size() << endl;
}

int nrand(int n) {
//    cout << "Input n: " << n << endl;
    if (n <= 0 || n > RAND_MAX) {
  //      throw domain_error("Argument to nrand is out of range");
        ++n;
    }
    const int bucket_size = RAND_MAX/n;
    int r;
    do r = rand() / bucket_size;
    while (r >= n);
    return r;
}

void printnode(map <int, list<int> >& a, int n) {
    for (listit it = a[n].begin(); it != a[n].end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}