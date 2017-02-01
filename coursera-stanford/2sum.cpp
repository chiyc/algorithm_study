// hash2sum.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <set>

using std::cin;		using std::set;     using std::list;
using std::endl;    using std::cout;


int main() {
	set<long long> values;
	long long i;
	while (cin >> i) {
		values.insert(i);
	}
	long long targetpairs = 0;

/*
	for (unordered_set<long long>::iterator it = values.begin(); it != values.end(); ++it) {
		for (long long z = -10000 - (*it); z != 10001 - (*it); ++z) {
			if (values.count(z) == 1) {
				cout << "x = " << *it << "\t and y =  " << ;
				++targetpairs;
			}
		}
	}
*/

	for (long long z = -10000; z != 10001; ++z) {
		for (set<long long>::iterator it = values.begin(); it != values.end(); ++it) {
			if (values.count(z - *it) == 1) {
				++targetpairs;
				cout << "x = " << *it << "\t and y =  " << z - *it << "\t sum to " << z << endl;
				break;
			}
		}
	}

	cout << targetpairs << endl;
}

