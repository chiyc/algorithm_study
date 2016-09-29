#include <map>
#include <list>
#include <iostream>
#include <string>
#include <sstream>

using std::list;    using std::cout;    using std::cin;     using std::istringstream;
using std::map;     using std::endl;    using std::string;

int karger(map <int, list<int> >&);
void contraction(map <int, list<int> >&);

int main() {
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

    for (list<int>::iterator i = adj[183].begin(); i != adj[183].end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;

    

}

int karger(map <int, list<int> >& a) {
    while (a.size() > 2) {
        contraction(a);
    }
    return a.begin()->second.size();
}

void contraction(map <int, list<int> >& a) {
    map <int, list<int> > random_it = a.begin();
    // generate random number out of size of a
    int rand;
    random_it += rand;
    //generate random edge from the list associated with the random node

    
}