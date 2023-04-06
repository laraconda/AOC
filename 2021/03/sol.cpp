#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    string l;
    vector<int> ns;
    const int N = 12;
    while (getline(cin, l)) {
        ll n = stoll(l, nullptr, 2);
        ns.push_back(n);
    }
    ll gen = 0;
    ll scrub = 0;
    for (int i=0; i<N; i++) {
        int cgen = 0;
        int bngen = 0;
        for (ll x : ns) {
            if (((x >> N - i) ^ gen) == 0) {
                bngen++;
                if ((x >> (N - 1 - i)) & 1) {
                    cgen++; 
                }
            }
        }
        gen <<= 1;
        if (cgen >= (bngen - cgen)) {
            gen |= 1;
        }
    }
    for (int i=0; i<N; i++) {
        int cscrub = 0;
        int bnscrub = 0;
        ll lastx = 0;
        for (ll x : ns) {
            if (((x >> N - i) ^ scrub) == 0) {
                bnscrub++;
                lastx = x;
                if ((x >> (N - 1 - i)) & 1) {
                    cscrub++; 
                }
            }
            
        }
        scrub <<= 1;
        if (cscrub < (bnscrub - cscrub)) {
            scrub |= 1;
        }
        if (bnscrub == 1) {
            scrub = lastx; 
            break;
        }
    }
    
    cout << gen * scrub << endl;
}
