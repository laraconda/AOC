#include <bits/stdc++.h>
using namespace std;

int fval(char c) {
    int val = 0;
    if (isupper(c))
        val = (c - 'A') + 27;
    else
        val = (c- 'a') + 1;
    return val;
}

int main() {
    string l;
    int p = 0;
    int s = 0;
    map<char, int> m;
    while (getline(cin, l)) {
        int n = l.size();

        set<char> ss;
        for (int i=0; i<n; i++) {
            ss.insert(l[i]);
        }
        for (char c : ss) {
            m[c]++;
        }

        if (p == 2) {
            for (auto kv : m) {
                if (kv.second == 3)
                    s+=fval(kv.first);
            }
            m.clear();
        }

        p++;
        p = p%3;
    }
    cout << s << endl;
}
