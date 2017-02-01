#include <vector>
#include <iostream>

using std::vector;  using std::cout;
using std::cin;     using std::endl;

void quicksort(vector<int>&, vector<int>::size_type, vector<int>::size_type,
               unsigned long long&);
int partition(vector<int>&, vector<int>::size_type, vector<int>::size_type);
void choosepivot1(vector<int>&, vector<int>::size_type, vector<int>::size_type);
void choosepivot2(vector<int>&, vector<int>::size_type, vector<int>::size_type);
void choosepivot3(vector<int>&, vector<int>::size_type, vector<int>::size_type); 
void swap(vector<int>&, vector<int>::size_type, vector<int>::size_type);
void printvec(vector<int>&);

int main() {
    vector<int> num;
    int s;
    while (cin >> s) {
        num.push_back(s);
    }
    unsigned long long c = 0; 
    quicksort(num, 0, num.size() - 1, c);
    cout << "Comparisons: " << c << endl;
    return 0;
}

void printvec(vector<int>& v) {
    for(vector<int>::size_type i = 0; i != v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void quicksort(vector<int>& input, vector<int>::size_type l, 
               vector<int>::size_type r, unsigned long long& c) {
    if (r > l && r < input.size()) {
        c += r - l;
        choosepivot3(input, l, r);
/*        cout << "Input the following vector: "<< endl;
        printvec(input);
        cout << "with limits " << l << " and " << r << endl;
*/        int p = partition(input, l, r);
/*        cout << endl << "Partition function output: " << endl;
        printvec(input);
        cout << "Using pivot point " << p << endl << endl;
 */       quicksort(input, l, p - 1, c);
        quicksort(input, p + 1, r, c);
    }

}

int partition(vector<int>& input, vector<int>::size_type l, 
              vector<int>::size_type r) {
    int pivot = input[l];
    int p = l + 1;
    for (int j = l + 1; j <= r; ++j) {
        if (input[j] < pivot) {
            swap(input, p, j);
            ++p;
        }
    }
    swap(input, l, p - 1); 
    return p - 1;
}

void swap(vector<int>& v, vector<int>::size_type a, vector<int>::size_type b){
    int swap = v[a];
    v[a] = v[b];
    v[b] = swap;
}

void choosepivot1(vector<int>& input, vector<int>::size_type l, 
                  vector<int>::size_type r) {

}

void choosepivot2(vector<int>& input, vector<int>::size_type l, 
                  vector<int>::size_type r) {
    swap(input, l, r);
}

void choosepivot3(vector<int>& input, vector<int>::size_type l, 
                  vector<int>::size_type r) {
    
    int m = (l + r) / 2;
    vector<int> v;
    v.push_back(input[l]);
    v.push_back(input[m]);
    v.push_back(input[r]);
    vector<int> vi;
    vi.push_back(l); vi.push_back(m); vi.push_back(r);
    for (int i = 0; i != 3; ++i) {
        int min = 10001;
        int mini = -1;
        for (int j = i; j != 3; ++j) {
            if (v[j] < min) {
                min = v[j];
                mini = j;
            }
        }
        swap(v, i, mini);
        swap(vi, i, mini);
    }
    swap(input, l, vi[1]);
    
}
           
        
        
            
