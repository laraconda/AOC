#include <bits/stdc++.h>
using namespace std;

int main() {
    int p;
    vector<int> ps;
    while (scanf("%d,", &p) != EOF) {
        ps.push_back(p); 
    }
    int ans = 1e9;
    for (int p=0; p<=2000; p++) {
        int sc = 0;
        for (int s : ps) {
            int d = abs(s - p);
            sc += (d*(d+1))/2;
        }
        ans = min(sc, ans);
    }
    cout << ans << endl;
}
