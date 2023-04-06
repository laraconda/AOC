#include <bits/stdc++.h>
using namespace std;

int main() {
    string n;
    priority_queue<long long> pq;
    long long s = 0;
    while (getline(cin, n)) {
        if (n != "") {
            long long N = stoll(n);
            s += N;
        } else {
            pq.push(s);
            s = 0;
        }
    }
    pq.push(s);
    long long ans = 0;
    for (int i=0; i<3; i++) {
        ans += pq.top();
        pq.pop();
    }
    cout << ans << endl;
}
