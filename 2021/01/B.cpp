#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    int i = 0;
    int d;
    ll s = 0;
    int co = 0;
    ll prev = -1;
    int a=0,b=0,c=0;
    while (cin >> d) {
        s += d;
        if (i >= 2) {
            if (i % 3 == 0) {
                s -= a;
                a = d;
            } else if (i % 3 == 1) {
                s -= b;
                b = d;
            } else {
                s -= c;
                c = d;
            }
            if (prev != -1 && s > prev) co++;
            prev = s;
        }
        i++;
    }
    cout << co << endl;
}
