#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::cin;     using std::endl;    using std::priority_queue;
using std::cout;    using std::vector;  using std::sort;

int main() {
    vector<int> v;
    int num;
    long result = 0;
    while (cin >> num) {
        v.push_back(num);
        sort(v.begin(), v.end());
        result += v[(v.size() - 1) / 2] % 10000;
        result = result % 10000;
    }
    cout << result;
}