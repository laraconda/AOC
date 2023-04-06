#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<stack<char>> v(10);
    v[1] = stack<char> ({'Q','W','P','S','Z','R','H','D'}); 
    v[2] = stack<char> ({'V','B','R','W','Q','H','F'}); 
    v[3] = stack<char> ({'C','V','S','H'}); 
    v[4] = stack<char> ({'H','F','G'}); 
    v[5] = stack<char> ({'P','G','J','B','Z'}); 
    v[6] = stack<char> ({'Q','T','J','H','W','F','L'}); 
    v[7] = stack<char> ({'Z','T','W','D','L','V','J','N'}); 
    v[8] = stack<char> ({'D','T','Z','C','J','G','H','F'}); 
    v[9] = stack<char> ({'W','P','V','M','B','H'}); 

    int q;
    int o;
    int d;
    while (scanf("move %d from %d to %d\n", &q, &o, &d) != EOF) {
        vector<char> rev;
        while (q--) {
            char x = v[o].top(); v[o].pop();
            rev.push_back(x);
        }
        reverse(rev.begin(), rev.end());
        for (char x : rev) v[d].push(x);
    }
    for (int i=1; i<10; i++) {
        cout << v[i].top();
    }
    cout << endl;
}
