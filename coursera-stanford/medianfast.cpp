#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::cin;     using std::endl;    using std::priority_queue;
using std::cout;    using std::vector;  using std::sort;



int main() {
    priority_queue<int, std::vector<int>, std::greater<int> > top_half;
    priority_queue<int> bot_half;
    
    int count = 0;
    int num;
    int med;
    long result = 0;

    int a;
    int b;
    cin >> a;
    result += a;
    cin >> b;
    if (a > b) {
        top_half.push(a);
        bot_half.push(b);
    }
    else {
        top_half.push(b);
        bot_half.push(a);
    }
    result += bot_half.top();

    while (cin >> num) {

        if (num < top_half.top()) {
            bot_half.push(num);
        }
        else if (num > bot_half.top()) {
            top_half.push(num);
        }
        
        if (top_half.size() > bot_half.size() ) {
            int pop = top_half.top();
            top_half.pop();
            bot_half.push(pop);
        }
        if (bot_half.size() - top_half.size() > 1) {
            int pop = bot_half.top();
            bot_half.pop();
            top_half.push(pop);
        }

        result += bot_half.top() % 10000;
        result = result % 10000;
    }
    cout << result << endl;
}