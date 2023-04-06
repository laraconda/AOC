#include <bits/stdc++.h>
using namespace std;

int main() {
    string l;
    getline(cin, l);
    int n = l.size();
    for (int i=0;i<n-14;i++) {
        bool diff = true;
        for (int j=i; j<i+14; j++) {
            for (int k=j+1; k<i+14; k++) {
                if (l[j] == l[k]) diff = false;
            }
        }
        if (diff) {
            cout << i + 14 << endl;
            break;
        }
    }
}
