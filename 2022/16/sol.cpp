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
        for (auto& ne : vnes.se)
            nes[i].pb(distance(ness.begin(), ness.find(ne)));
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
}

map<ui, int> dp;

int findnzidx(int val) {
    if (!nz.count(val)) return -1;
    else return nz[val];
}

ui joinstate(int val, int ele, int mask, int remm) {
    ui loc = ((ui)val << 6) | ele;
    ui rm = (mask << 5) | remm;
    return (loc << 20) | rm;
}

pair<pii, pii> getmr(ui state) {
    int val = state >> 26;
    int ele = 0;
    for (int i=25; i>19; i--) {
        ele |= (state >> i) & 1;
        if (i > 20)
            ele <<= 1;
    }
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
    return {{val, ele}, {mask, remm}};
}

ll newstate = 0;
int printstates = 1e6;
int iters = 0;

int mp(ui state) {
    pair<pii, pii> vlmr = getmr(state);
    int val = vlmr.fi.fi;
    int ele = vlmr.fi.se;
    int mask = vlmr.se.fi;
    int remm = vlmr.se.se;
    if (remm == 0) return 0;
    if (dp.count(state)) return dp[state];
    newstate++;
    if (iters++ % 1e6) cout << "states: " << newstate << endl;
    int ans = -1;
    int validx = findnzidx(val);
    int eleidx = findnzidx(ele);
    for (auto ne : nes[val]) { // move move
        for (auto neele : nes[ele]) {
            iu nstate = joinstate(ne, neele, mask, remm - 1);
            int r = mp(nstate);
            ans = max(ans, r);
        }
    }
    if (validx != -1) {
        if (!((mask >> validx) & 1)) { // val cerrada | open open
            int nmask = mask | (1 << validx);
            if (eleidx != -1 && !((nmask >> eleidx) & 1)) { // ele cerrada
                nmask = nmask | (1 << eleidx);
                state = joinstate(val, ele, nmask, remm - 1);
                int op = mp(state);
                op += valvrate[ele] * (remm - 1);
                op += valvrate[val] * (remm - 1);
                mask &= ~(1 << eleidx);
                mask &= ~(1 << validx);
                state = joinstate(val, ele, mask, remm - 1);
                ans = max(ans, op);
            } else { // ele abierta | open move
                mask |= (1 << validx); 
                for (auto neele : nes[ele]) {
                    state = joinstate(val, neele, mask, remm - 1);
                    int op = mp(state) + valvrate[val] * (remm - 1);
                    ans = max(ans, op);
                }
                mask &= ~(1 << validx);
                state = joinstate(val, ele, mask, remm - 1);
            }
        } else { // val abierta
            if (eleidx != -1 && !((mask >> eleidx) & 1)) { // ele cerrada | move open
                mask |= (1 << eleidx);
                for (auto ne : nes[val]) {
                    state = joinstate(ne, ele, mask, remm - 1);
                    int op = mp(state) + valvrate[ele] * (remm - 1);
                    ans = max(ans, op);
                }
                mask &= ~(1 << eleidx);
                state = joinstate(val, ele, mask, remm - 1);
            } 
        }
    } else {
        if (eleidx != -1 && !((mask >> eleidx) & 1)) { // ele cerrada | move open
            mask |= (1 << eleidx);
            for (auto ne : nes[val]) {
                state = joinstate(ne, ele, mask, remm - 1);
                int op = mp(state);
                op += valvrate[ele] * (remm - 1);
                ans = max(ans, op);
            }
            mask &= ~(1 << eleidx);
            state = joinstate(val, ele, mask, remm - 1);
        } 
    }
    state = joinstate(val, ele, mask, remm);
    return dp[state] = ans;
}

int main() {
    mread();
    // room AA, room AA, no open valves, 26 mins
    ui state = joinstate(0, 0, 0, 26);
    cout << mp(state) << endl;
}
