#include <iostream>
#include <vector>
#include <string>

using std::cin;     using std::vector;  using std::endl;
using std::cout;    using std::string;

void mergesort(vector<long>&, vector<long>::size_type, vector<long>::size_type, vector<long>&, unsigned long long&);
void merge(vector<long>&, vector<long>::size_type, vector<long>::size_type, 
            vector<long>::size_type, vector<long>::size_type, vector<long>&, unsigned long long&);
void copyto(vector<long>&, vector<long>&, vector<long>::size_type, vector<long>::size_type);
void print(vector<long>&);

int main(){
    long s;
    vector<long> array;
    vector<long> copy;
    while(cin >> s){
        array.push_back(s);
        copy.push_back(s);
    }
    unsigned long long inversions = 0;
    mergesort(array, 0, array.size() - 1, copy, inversions);
    cout << "Sorted Array:" << endl;
    print(array);
    cout << "Inversions: " << inversions << endl;
    return 0;
}

void mergesort(vector<long>& input, vector<long>::size_type p, vector<long>::size_type r, vector<long>& copy, unsigned long long& count){
    if(p < r){
        vector<long>::size_type q1 = (p + r)/2;
        vector<long>::size_type q2 = q1 + 1; 
        mergesort(input, p, q1, copy, count);
        mergesort(input, q2, r, copy, count);
        merge(input, p, q1, q2, r, copy, count);
        copyto(copy, input, p, r);
//        cout << "Current Array" << endl;
//        prlong(input);
    }
}

void merge(vector<long>& input, vector<long>::size_type p1, vector<long>::size_type r1, 
            vector<long>::size_type p2, vector<long>::size_type r2, vector<long>& copy, unsigned long long& count){
    long inv = 0;
    for(vector<long>::size_type it = p1; it != r2 + 1; ++it){
        if( (p1<=r1 && input[p1]<input[p2]) || p2 > r2){
            copy[it] = input[p1];
            ++p1;
        }
        else{
            copy[it] = input[p2];
            ++p2;
            count += r1-p1 + 1;
        }
    }       
}

void copyto(vector<long>& source, vector<long>& dest, vector<long>::size_type from, vector<long>::size_type to){
    for(vector<long>::size_type i = from; i != to+1; ++i){
        dest[i] = source[i];
    }
}

void print(vector<long>& array){
    for(vector<long>::size_type i = 0; i != array.size(); ++i){
        cout << array[i] << " ";
    } 
    cout << endl;
}