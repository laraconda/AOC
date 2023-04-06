#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef unsigned int ui;

#define fi first
#define se second
#define endl '\n'
#define pb push_back
#define all(v) v.begin(), v.end()

map<string, vector<string>> ness;
map<string, int> valvrates;
vector<string> nzs;

map<int, int> nz;
map<int, int> valvrate;
map<int, vector<int>> nes;

const int N = 70;
const int INF = 1e9;
vector<vector<int>> dist(N, vector<int>(N, INF));

map<ui, int> dp;

void mread() {
    string l;
    while (getline(cin, l)) {
        stringstream ss(l);
        string trash;
        string val;
        int rate;
        ss >> trash;
        ss >> val;
        ss >> trash;
        ss >> trash;
        ss.ignore(6);
        ss >> rate;
        valvrates[val] = rate;
        if (rate > 0) {
            nzs.pb(val);
        }
        ss.ignore(1);
        for (int i=0; i<4; i++)
            ss >> trash;
        string ne;
        while (ss >> ne) {
            if (ne.back() == ',') {
                ne.pop_back();
            }
            ness[val].pb(ne);
        }
    }
    sort(all(nzs));

    int i=0;
    for (auto& vnes : ness) {
        for (auto& ne : vnes.se) {
            int j = distance(ness.begin(), ness.find(ne));
            nes[i].pb(j);
            dist[i][j] = 1;
        }
        i++;
    }
    for (auto& vrate : valvrates) {
        valvrate[distance(ness.begin(), ness.find(vrate.fi))] = vrate.se; 
    }
    i=0;
    for (auto& x : nzs) {
        nz[distance(ness.begin(), ness.find(x))] = i++;
    }
    ness.clear();
    valvrates.clear();
    nzs.clear();

    int n = ness.size();
    for (int k=0; k<n; k++) {
        dist[k][k] = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
               dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]); 
            }
        }
    }
}


int findnzidx(int val) {
    if (!nz.count(val)) return -1;
    else return nz[val];
}

ui joinstate(int val, int newp, int mask, int remm) {
    ui loc = (val << 1) | newp;
    ui rm = (mask << 5) | remm;
    return (loc << 20) | rm;
}

pair<pii, pii> getmr(ui state) {
    int val = state >> 21;
    int newp = (state >> 20) & 1;
    int mask = 0;
    for (int i=19; i>4; i--) {
        mask |= (state >> i) & 1;
        if (i > 5)
            mask <<= 1;
    }
    int remm = 0;
    for (int i=4; i>-1; i--) {
        remm |= (state >> i) & 1;
        if (i > 0)
            remm <<= 1;
    }
    return {{val, newp}, {mask, remm}};
}

ll newstate = 0;
ll printstates = 1e6;
ll iters = 0;

int mp(ui state) {
    pair<pii, pii> vlmr = getmr(state);
    int val = vlmr.fi.fi;
    int newp = vlmr.fi.se;
    int mask = vlmr.se.fi;
    int remm = vlmr.se.se;
    if (remm == 0) {
        if (newp) return mp(joinstate(0, 0, mask, 26));
        else return 0;
    }
    iters++;
    if (iters % printstates == 0) {
        cout << "states: " << newstate << " iters: " << iters << endl;
    }
    if (dp.count(state)) return dp[state];
    newstate++;
    int ans = -1;
    for (auto& ne : nz) {
        int d = dist[ne.fi][val];
        ui nstate = joinstate(ne.fi, newp, mask, max(0, remm - d));
        ans = max(ans, mp(nstate));
    }
    int validx = findnzidx(val);
    if (validx != -1 && !((mask >> validx) & 1)) {
        int nmask = mask | (1 << validx);
        ui nstate = joinstate(val, newp, nmask, remm - 1);
        int op = mp(nstate) + valvrate[val] * (remm - 1);
        ans = max(ans, op);
    }
    return dp[state] = ans;
}

int main() {
    mread();
    // room AA, another player, no open valves, 26 mins
    ui state = joinstate(0, 1, 0, 26);
    cout << mp(state) << endl;
    cout << "final states: " << newstate << " iters: " << iters << endl;
}
