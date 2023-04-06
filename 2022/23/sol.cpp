#include <bits/stdc++.h>
using namespace std;

const int E = 10;

const int N = 450;
const int M = 450;
const int SHIFT = 70;
vector<vector<int>> g(N, vector<int>(M, 0));
vector<vector<int>> di = {{-1,-1,-1}, {1,1, 1}, {-1,0,1}, {-1,0,1}};
vector<vector<int>> dj = {{-1, 0, 1}, {-1,0,1}, {-1,-1,-1}, {1,1,1}};
int didx = 0;

vector<int> ni = {-1,-1,-1,0,1,1,1,0};
vector<int> nj = {-1,0,1,1,1,0,-1,-1};

pair<int, int> boundi = {SHIFT + 3, SHIFT + 3};
pair<int, int> boundj = {SHIFT + 3, SHIFT + 3};

int oposite(int lo) {
    if (lo == 0) return 1;
    if (lo == 1) return 0;
    if (lo == 2) return 3;
    if (lo == 3) return 2;
}

bool round() {
    bool moved = false;
    vector<pair<pair<int, int>, int>> prop;
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            if (g[i][j] == E) {
                bool alone = true;
                for (int z=0; z<8; z++) {
                    int newi = i + ni[z];
                    int newj = j + nj[z];
                    if (g[newi][newj] == E) alone = false;
                }  
                if (!alone) {
                    int locali = didx;
                    int count = 0;
                    bool foundpos = false;
                    while (count < 4 && !foundpos) {
                        auto pi = di[locali];
                        auto pj = dj[locali];

                        // free to move to the dir defined by locali
                        bool f = true; 
                        // testing w or not is possible to move
                        for (int z=0; z<3; z++) {
                            int newi = i + pi[z];
                            int newj = j + pj[z];
                            if (g[newi][newj] == E) f = false;
                        }
                        // proposing
                        if (f) {
                            int newi = i + pi[1];    
                            int newj = j + pj[1];
                            g[newi][newj]++;
                            foundpos = true;
                            prop.push_back({{newi, newj}, locali});
                        }
                        count++;
                        locali = (locali + 1) % 4;
                    }
                }
            }
        }
    }
    /* end first part */
    for (auto pp : prop) { // checking w is the only prop
        int i = pp.first.first;
        int j = pp.first.second;
        int locali = pp.second;
        if (g[i][j] == 1) { // moving
            moved = true;
            g[i][j] = E;
            boundi.first = min(boundi.first, i);
            boundi.second = max(boundi.second, i);
            boundj.first = min(boundj.first, j);
            boundj.second = max(boundj.second, j);
            int opo = oposite(locali);
            int oi = i + di[opo][1];
            int oj = j + dj[opo][1];
            g[oi][oj] = 0; // removing from prev pos
        }
        if (g[i][j] != E) g[i][j] = 0; // back to 0
    }
    prop.clear();
    didx = (didx+1) % 4;
    return moved;
}

void mread() {
    string l;
    int n = 0;
    int i = 0;
    while(getline(cin, l)) {
        int m = l.size();
        for (int j=0; j<m; j++) {
            int ishift = i + SHIFT;
            int jshift = j + SHIFT;
            if (l[j] == '#') {
                g[ishift][jshift] = E; 
                boundi.first = min(boundi.first, ishift);
                boundi.second = max(boundi.second, ishift);
                boundj.first = min(boundj.first, jshift);
                boundj.second = max(boundj.second, jshift);
            } else if (l[j] == '.') {
                g[ishift][jshift] = 0; 
            } 
        }
        n++;
        i++;
    }
}

int freessq() {
    int mini = boundi.first;
    int maxi = boundi.second;
    int minj = boundj.first;
    int maxj = boundj.second;
    
    int count = 0;
    for (int i=mini; i<=maxi; i++) {
        for (int j=minj; j<=maxj; j++) {
            if (g[i][j] == 0) count++;
        }
    }
    return count;
}

int main () {
    mread();
    for (int r=0; true; r++) {
        bool moved = round();        
        if (!moved) {
            cout << "ans: " << r + 1 << endl;            
            break;
        }

    }
}
