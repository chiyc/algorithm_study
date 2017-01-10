// hash2sum.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <set>
#include <list>

using std::cin;		using std::set;     using std::list;
using std::endl;    using std::cout;


int main() {
	set<long long> values;
	long long i;
	
    list<int> notfound;
    set<int> found;
	for(long i = -10000; i != 10001; ++i) {
		notfound.push_back(i);
	}
	
	long long targetpairs = 0;

	while (cin >> i) {
		values.insert(i);
	}
	

	for (set<long long>::iterator setit = values.begin(); setit != values.end(); ++setit) {
		for (list<int>::iterator tit = notfound.begin(); tit != notfound.end(); ++tit) {
			if (values.count(*tit - *setit) == 1) {
				++targetpairs;
				cout << "x = " << *setit << "\t and y =  " << *tit - *setit << "\t sum to " << *tit << endl;
				found.insert(*tit);
				tit = notfound.erase(tit);
			}
		}
	}

	cout << found.size() << endl;
}

