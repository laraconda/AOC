#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int M = 130;
const int N = 30;


vector<vector<int>> g(N, vector<int>(M, 0));
vector<vector<int>> ig(N, vector<int>(M, 0));

vector<int> ni = {0,-1,0,1,0};
vector<int> nj = {0,0,1,0,-1};

int n = 0;
int m = 0;

void mread() {
    string l;
    int i = 0;
    while (getline(cin, l)) {
        m = l.size();
        for (int j=0; j<(int)l.size(); j++) {
            if (l[j] == '^') {
                ig[i][j] = 1;
            } else if (l[j] == '<') {
                ig[i][j] = 4;
            } else if (l[j] == '>') {
                ig[i][j] = 2;
            } else if (l[j] == 'v') {
                ig[i][j] = 3;
            }
        }  
        i++;
    }
    n = i-2;
    m-=2;
    cout << "n: " << n << " m: " << m << endl;
}

void sim(int steps) {
    
    for (int i=0; i<=n+1; i++)
        for (int j=0; j<=m+1; j++)
            g[i][j] = 0;

    for (int i=0; i<=n+1; i++) {
        for (int j=0; j<=m+1; j++) {
            if (i == 0 || j == 0 || i == n+1 || j == m+1)
                g[i][j] = 5;
            if (ig[i][j] == 1) {
                int newi = i - (steps % n);
                if (newi <= 0) newi+=n;
                if (newi == 0 || newi == n+1) cout << "bad calc!!" << endl;
                g[newi][j] = 1;
            } else if (ig[i][j] == 3) {
                int newi = i + (steps % n);
                if (newi > n) newi %= n;
                if (newi == 0 || newi == n+1) cout << "bad calc!!" << endl;
                g[newi][j] = 3;
            } else if (ig[i][j] == 4) {
                int newj = j - (steps % m);
                if (newj <= 0) newj+=m;
                if (newj == 0 || newj == m+1) cout << "bad calc!!" << endl;
                g[i][newj] = 4;
            } else if (ig[i][j] == 2) {
                int newj = j + (steps % m);
                if (newj > m) newj %= m;
                if (newj == 0 || newj == m+1) cout << "bad calc!!" << endl;
                g[i][newj] = 2;
            }
        } 
    }
    g[0][1] = 0;
    g[n+1][m] = 0;
}


int md(pii a, pii b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

map<int, int> dp;

int mstate(int time, int i, int j, int ti) {
    return (((time << 7 | i) << 7 | j) << 2 | ti); 
}

void mprint(int t) {
    cout << "time: " << t << endl;
    for (int i=0; i<=n+1; i++) {
        for (int j=0; j<=m+1; j++) {
            if (g[i][j] == 0) {
                cout << ".";
            } else if (g[i][j] == 1) {
                cout << "^"; 
            } else if (g[i][j] == 2) {
                cout << ">"; 
            } else if (g[i][j] == 3) {
                cout << "v"; 
            } else if (g[i][j] == 4) {
                cout << "<"; 
            } else if (g[i][j] == 5) {
                cout << "#"; 
            }
        }
        cout << endl;
    }
}

unordered_set<int> vis;

int rec(int t, pii pos, pii start, pii goal, int dl, int startt, int ti) {
    int ans = 1e7;
    int dt = t - startt;
    if (dt >= dl) return ans;
    if (pos == goal) return t;
    int i = pos.first;
    int j = pos.second;
    if (i < 0 || i > n+1 || j < 0 || j > m+1) return ans;
    sim(t);
    if (g[i][j]) return ans;
    if (md(start, pos) > 5 && md(start, pos) < (int)dt*0.3) return ans;
    int state = mstate(t,i,j,ti);
    if (dp.count(state)) return dp[state];
    for (int z=0; z<5; z++) {
        int newi = i+ni[z];
        int newj = j+nj[z];
        if (newi < 0 || newi > n+1 || newj < 0 || newj > m+1) continue;
        int mhash = newi << 15 | newj;
        if (z != 0 && vis.count(mhash)) continue;
        vis.insert(mhash);
        ans = min(
                ans,
                rec(t + 1, {i+ni[z], j + nj[z]}, start, goal, dl, startt, ti)
        );
        vis.erase(mhash);
    }
    return dp[state] = ans;
}

int main() {
    mread();
    int dl = 320;
    pii sta = {0, 1};
    int stah = 0 << 15 | 1;
    int eeeh = (n+1) << 15 | m;
    pii eee = {n+1, m};
    vis.insert(stah);
    int ar = rec(0, sta, sta, eee, dl, 0, 0);
    vis.erase(stah);
    cout << "ar: " << ar << endl;
    vis.insert(eeeh);
    // int br = rec(ar, eee, eee, sta, dl, ar, 1);
    vis.erase(eeeh);
    //cout << "br: " << br << endl;
    vis.insert(stah);
    // int cr = rec(br, sta, sta, eee, dl, br, 2);
    vis.erase(stah);
    //cout << "ans: " << cr << endl;
}
