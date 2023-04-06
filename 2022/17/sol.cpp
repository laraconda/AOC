#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int W = 7;
const int N = 2e5 + 3;
const int NSIM = 2e4;
vector<vector<vector<int>>> shapes(5);
vector<vector<int>> g(N, vector<int>(W, 0));

int mgcd(vector<int> v) {
    int gc = v.back();
    for (int x : v) {
        gc = __gcd(gc, x);
    }
    return gc;
}

int wi(int r) {
    return shapes[r][0].size();
}
int he(int r) {
    return shapes[r].size();
}

bool coli(int r, int i, int j) {
    for (int ii=i; ii < i + he(r); ii++) {
        for (int jj=j; jj < j + wi(r); jj++) {
            if (shapes[r][ii - i][jj - j] && g[ii][jj])
                return true;
            }
        }
    return false;
}

void unpaint(int r, int i, int j) {
    for (int ii=i; ii<i+he(r); ii++) {
        for (int jj=j; jj < j + wi(r); jj++) {
            if (shapes[r][ii - i][jj - j] && g[ii][jj] == 2) {
                g[ii][jj] = 0; // careful 
            }
        }
    }
}
void mpaint(int r, int i, int j, bool solid) {
    for (int ii=i; ii<i+he(r); ii++) {
        for (int jj=j; jj < j + wi(r); jj++) {
            if (shapes[r][ii - i][jj - j]) {
                g[ii][jj] = (solid) ? 1 : 2;
            }
        }
    }
}


void mprint(int top, int r, int i, int j, char w, bool solid) {
    mpaint(r, i, j, solid);
    cout << "r:" << r << " w: " << w << endl;
    for (int i=top - 7; i<min(top+15, N); i++) {
        for (int j=0; j<W; j++) {
            cout << g[i][j];
        }
        cout << endl;
    }
    unpaint(r, i, j);
    cout << "----------" << endl;
}
                


int main() {
    string line;
    getline(cin, line);
    cout << "line size: " << line.size() << endl;
    shapes[0] = {{1,1,1,1}};

    shapes[1] = {{0,1,0},
                {1,1,1},
                {0,1,0}};

    shapes[2] = {{0,0,1},
                {0,0,1},
                {1,1,1}};
    
    shapes[3] = {{1},
                {1},
                {1},
                {1}};

    shapes[4] = {{1,1},
                {1,1}};
  
    for (int j=0; j<W; j++) {
        g[N-1][j] = 1;
    }
    int top = N-1;
    int gas = 0;
    int height = 0 ;
    vector<int> hes(NSIM+1);
    hes[0] = 0;
    for (int k=0; k<NSIM; k++) { // keep rocks comming
        int r = k % 5;

        int i = top - 3 - he(r);
        if (top < 10) break;
        int j = 2;
        int jend = j + wi(r) - 1;
        for (int fall=0; true; fall++) {  // rock falling
            char w = line[gas];
            if (w == '<') {
                j = max(0, j-1);
                jend = j + wi(r) - 1; 
                if (coli(r, i, j)) {
                    j = j+1;
                    jend = j + wi(r) - 1;
                }
            } else if (w == '>'){
                jend = min(6, jend + 1); 
                j = jend - wi(r) + 1;
                if (coli(r, i, j)) {
                    j = j-1;
                    jend = j + wi(r) - 1;
                }
            } 
            w = 'v';
            gas++;
            gas%=line.size();
            i++;
            if (coli(r, i, j)) {
                top = min(top, i-1);
                mpaint(r, i-1, j, true);
                break;
            }
        }
        height = N - 1 - top;
        hes[k+1] = height;
    }
   
    ll realans = 1514285714288;
    ll step = 1e12;
    int stepi = 1;
    int stepj = 1;
    vector<int> difs;
    map<ll, int> mm;
    for (int i=0; i<hes.size(); i+=stepi) {
        for (int j=i+stepj; j<hes.size(); j+=stepj) {
            if ((j - i) % 35 != 0) continue;
            ll dh = hes[j] - hes[i];
            int tmp = j;
            int z = j + (j - i);
            bool cy = true;
            while (z < hes.size()) {
                ll tempt = ((z - i) / (j-i))*dh + hes[i];
                if (dh != ((ll)hes[z] - hes[tmp])|| (((z - i) % (j-1)) == 0 && tempt != hes[z])) {
                    cy = false;        
                    break;
                }
                tmp = z;
                z += (j - i);
            }
            if (cy) {
                if ((step - i) % (j-i) == 0) {
                    ll ans = ((step - i) / (j-i))*dh + hes[i];
                    mm[ans]++;
                }
            }
        }
    }
    cout << "number of different answers: " << mm.size() << endl;
    vector<pair<ll,ll>> vv;
    for (auto& x : mm) {
        vv.push_back({x.second, x.first});
    }
    sort(vv.begin(), vv.end());
    int nvv = vv.size();
    cout << "most common: " << vv.back().second << " with: " << vv.back().first << endl;
    // cout << "second most common: " << vv[nvv-2].second << " with: " << vv[nvv-2].first << endl;
}
