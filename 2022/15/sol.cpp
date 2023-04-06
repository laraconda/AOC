#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

typedef pair<ll, ll> pii;
const int N = 26;
const int MAX = 4000000;
vector<ll> mdist(N);
vector<pii> sens(N);
vector<pii> bs(N);
ll minx = 1e17;
ll maxx = -1e17;


void mread() {
    string l;
    int i = 0;
    while (getline(cin, l)) {
        stringstream ss(l);
        ll x;
        ll y;
        ss.ignore(12);
        ss >> x;
        minx = min(x,minx);
        maxx = max(x, maxx);
        ss.ignore(4);
        ss >> y;
        sens[i] = {x, y};
    
        ss.ignore(25);
        ss >> x;
        minx = min(x,minx);
        maxx = max(x, maxx);
        ss.ignore(4);
        ss >> y;
        bs[i] = {x, y};

        i++;
    }
}

ll mandist(pii a, pii b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void calc() {
    for (int i=0; i<sens.size(); i++) {
        ll md = 1e17;
        for (int j=0; j<bs.size(); j++) {
            ll d = mandist(sens[i], bs[j]);
            md = min(md, d);
        }
        mdist[i] = md; 
    }
}


int main() {
    mread();
    calc();
    map<pii, int> ms;
    for (int i=0; i<N; i++) {
        int d = mdist[i];
        for (int z=0; z<d+1; z++) {
            pii a = {sens[i].first + (d+1) - z, sens[i].second - z};
            if (a.second >= 0 && a.first >= 0 && a.second <= MAX && a.first <= MAX)
                ms[a]++;
            a = {sens[i].first - z, sens[i].second - (d+1) + z};
            if (a.second >= 0 && a.first >= 0 && a.second <= MAX && a.first <= MAX)
                ms[a]++;
            a = {sens[i].first - (d+1) + z, sens[i].second + z};
            if (a.second >= 0 && a.first >= 0 && a.second <= MAX && a.first <= MAX)
                ms[a]++;
            a = {sens[i].first + z, sens[i].second + (d+1) - z};
            if (a.second >= 0 && a.first >= 0 && a.second <= MAX && a.first <= MAX)
                ms[a]++;
        }
    }
  
    set<pii> s;
    for (auto& e : ms) {
        if (e.second >= 2) {
            bool covered = false;
            for (int i=0; i<N; i++) {
                ll md = mandist(e.first, sens[i]);
                if (md <= mdist[i]) {
                    covered = true;
                    break;
                }
            }
            if (!covered) {
                s.insert(e.first); 
            }
        }
    }

    cout << s.size() << endl;
    for (auto& c: s) {
        ll ans = MAX * c.first + c.second;
        cout << "ans: " << ans << endl;
    }
    
    /*
    unordered_set<ll> s;
    ll yans = 2000000;
    for (ll x=minx - 10000000; x<=maxx + 10000000; x++) {
        for (int i=0; i<sens.size(); i++) {
            ll d = mandist({x, yans}, sens[i]); 
            if (d <= mdist[i]) s.insert(x);
        }
    }
    for (int i=0; i<N; i++) {
        if (bs[i].second == yans) {
            if (s.count(bs[i].first)) {
            }
            s.erase(bs[i].first);
        }
    }
    cout << "silver: " << s.size()<< endl;
    */
}
