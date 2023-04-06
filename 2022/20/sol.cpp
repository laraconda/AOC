#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;
vector<pii> as;
const ll deckey = 811589153;

void mread() {
    ll ai;
    int i=0;
    while (cin >> ai) {
        ai*=deckey;
        as.push_back({ai, i++});
    }
}

bool mf(const pii a, const pii b) {
    return a.second < b.second;
}

int main() {
    mread();
    int n = as.size();
    int t = 10;
    while (t--) {
        for (int i=0; i<n; i++) {
            ll ai = as[i].first % (n-1);
            int p = as[i].second;
            int np;
            if (ai < 0) {
                if (p + ai < 0) { // forw
                    np = p + (n - 1 + ai);
                } else { // back
                    np = p + ai; 
                }
            } else {
                if (p + ai >= n) { // back
                    np = (p + ai + 1) % n; 
                } else {  // forw
                    np = p + ai;
                }
            }
            if (np > p) {
                for (int j=0; j<n;j++) {
                    int ajs = as[j].second;
                    if ((p < ajs) && (ajs <= np)) {
                        as[j].second--;
                        if (as[j].second < 0) as[j].second += n;
                    }
                }
            } else {
                for (int j=0; j<n;j++) {
                    int ajs = as[j].second;
                    if (np <= ajs && ajs < p) {
                        as[j].second++; 
                        if (as[j].second >= n) as[j].second %= n;
                    }
                }
            }
            as[i].second = np;
        }
        /*
        vector<pii> c(as);
        cout << "mix: " << 10 - t << endl;
        sort(c.begin(), c.end(), mf);
        for (int i=0; i<n;i++)
            cout << c[i].first << " ";
        cout << endl;
        */
    }
    sort(as.begin(), as.end(), mf);
    cout << "final: " << endl;
    for (int i=0; i<n;i++)
        cout << as[i].first << " ";
    cout << endl;

    int zi = -1;
    for (int i=0; i<n; i++) {
        if (as[i].first == 0) {
            zi = i; 
        }
    }
    ll ans = 0;
    for (int i=1; i<4; i++) {
        int ii = (zi + i*1000) % n;
        ans+=as[ii].first;
        cout << "ith: " << as[ii].first<<" ";
    }
    cout << endl;
    cout << ans << endl; 
}
