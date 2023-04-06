#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    string l;
    ll X = 0;
    ll Y = 0;
    ll a = 0;
    while (getline(cin, l)) {
        if (l[0] == 'f') { // forward 4
            int x = stoi(l.substr(8, (int)l.size() - 8));
            X +=x;
            Y +=x*a;
        } else if (l[0] == 'd') { // down 3
            int x = stoi(l.substr(5, (int)l.size() - 5));
            a += x;
        } else { // up 3
            int x = stoi(l.substr(3, (int)l.size() - 3));
            a -= x;
        }
    }
    cout << Y*X << endl;
}
