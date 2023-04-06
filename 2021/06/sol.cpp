#include <bits/stdc++.h>
using namespace std;

int main() {
    map<int, long long> a;
    map<int, long long> b;
    int f;
    while (scanf("%d,", &f) != EOF) {
        a[f]++;
    }
    for (int d=1; d<=256; d++) {
        if (d % 2 == 1) {
            for (auto fq : a) {
                int f = fq.first;
                long long q = fq.second;
                if (f == 0) {
                    b[6]+=q;
                    b[8]+=q;
                } else {
                    b[f-1]+=q;
                }
            }
            a.clear();
        } else {
            for (auto fq : b) {
                int f = fq.first;
                long long q = fq.second;
                if (f == 0) {
                    a[6]+=q;
                    a[8]+=q;
                } else {
                    a[f-1]+=q;
                }
            }
            b.clear();
        }
        if (d == 256) {
            long long ans = 0;
            for (auto fq:a) {
                ans+=fq.second;
            }
            cout << ans << endl;
        }
    }
}
