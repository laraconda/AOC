#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

// down, left, up, right
vector<int> pi = {0, 1, 0, -1, 0};
vector<int> pj = {0, 0, -1, 0, 1};

const int L = 1e5 + 5;
const int R = 1e5 + 6;

const int N=300;
const int M=300;

vector<vector<int>> g(N,vector<int>(M, 0)); // 1 walkable, 2 wall, 0 void
vector<int> ins;

int d=4;
pair<int, int> p = {0,0}; // CHANGE!!!!
int n = 0;
int m = 0;
int F = 50;

void mread() {
    string l;
    int ii = 0;
    int startj=-1;
    bool readins = false;
    while (getline(cin, l)) {
        int nl = l.size();
        if (!readins) {
            for (int i=0; i<nl; i++) {
                if (l[i] == '.') {
                    g[ii][i] = 1;
                    if (ii==0 && startj == -1) startj = i;
                } else if (l[i] == '#') {
                    g[ii][i] = 2;
                } else if (l[i] == ' ') {
                    ;
                } else {
                    readins = true;
                    break;
                }
            }
            if (!readins) {
                m = max(nl, m);
                ii++;
            }
        }
        if (readins) {
            int lastj = 0;
            for (int j=0; j<nl; j++) {
                if (l[j] == 'L') {
                    int num = stoi(l.substr(lastj, j - lastj));
                    ins.push_back(num);
                    lastj = j+1;
                    ins.push_back(L);
                } else if (l[j] == 'R') {
                    int num = stoi(l.substr(lastj, j - lastj));
                    ins.push_back(num);
                    lastj = j+1;
                    ins.push_back(R);
                } else {
                    continue; 
                }
            }
            int num = stoi(l.substr(lastj, nl - lastj));
            ins.push_back(num);
        }
    }
    n = ii-1;
    p.se = startj;
}

void turn(int c) {
    if (c == L) {
        d--;
        if (d == 0) d = 4;
    } else {
        d++;
        if (d == 5) d = 1;
    }
}


bool border() {
    int initiald = d;
    int i = p.fi;
    int j = p.se;
    if (i == 0 && 50 <= j && j < 100 && d == 3) { // e A
        d = 4; 
        p.fi = 150 + (j - 50);
        p.se = 0;
    } else if (150 <= i && i < 200 && j == 0 && d == 2) { // e F
        d = 1; 
        p.fi = 0;
        p.se = i - 100;
    } else if (0 <= i && i < 50 && j == 100 && d == 4) { // a A
        d = 4; 
        p.fi = p.fi;
        p.se = 100;
    } else if (0 <= i && i < 50 && j == 100 && d == 2) { // a B
        d = 2; 
        p.fi = i;
        p.se = 99;
    } else if (i == 49 && 50 <= j && j < 100 && d == 1) { // b A
        d = 1; 
        p.fi = 50;
        p.se = j;
    } else if (i == 50 && 50 <= j && j < 100 && d == 3) { // b C
        d = 3; 
        p.fi = 49;
        p.se = j;
    } else if (0 <= i && i < 50 && j == 50 && d == 2) { // y A
        d = 4; 
        p.fi = 149 - i;
        p.se = 0;
    } else if (100 <= i && i < 150 && j == 0 && d == 2) { // y E
        d = 4; 
        p.fi = 149 - i;
        p.se = 50;
    } else if (i == 49 && 100 <= j && j < 150 && d == 1) { // z B
        d = 2; 
        p.fi = 50 + (j - 100);
        p.se = 99;
    } else if (50 <= i && i<100 && j == 99 && d == 4) { // z C
        d = 3; 
        p.fi = 49;
        p.se = 100 + (i - 50);
    } else if (i == 0 && 100 <= j && j < 150 && d == 3) { // n B
        d = 3; 
        p.fi = 199;
        p.se = (j - 100);
    } else if (i == 199 && 0 <= j && j < 50 && d == 1) { // n F
        d = 1; 
        p.fi = 0;
        p.se = 100 + j;
    } else if (0 <= i && i < 50 && j == 149 && d == 4) { // m B
        d = 2; 
        p.fi = 99 + (50 - i);
        p.se = 99;
    } else if (100 <= i && i < 150 && j == 99 && d == 4) { // m D
        d = 2; 
        p.fi = 49 - (i - 100);
        p.se = 149;
    } else if (50 <= i && i < 100 && j==50 && d == 2) { // x C
        d = 1; 
        p.fi = 100;
        p.se = (i - 50);
    } else if (i == 100 && 0 <= j && j < 50 && d == 3) { // x E
        d = 4; 
        p.fi = 50 + j;
        p.se = 50;
    } else if (i == 99 && 50 <= j && j < 100 && d==1) { // c C
        d = 1; 
        p.fi = 100;
        p.se = j;
    } else if (i == 100 && 50 <= j && j < 100 && d == 3) { // c D
        d = 3; 
        p.fi = 99;
        p.se = j;
    } else if (100 <= i && i < 150 && j == 50 && d == 2) { // d D
        d = 2; 
        p.fi = i;
        p.se = 49;
    } else if (100 <= i && i < 150 && j == 49 && d == 4) { // d E
        d = 4; 
        p.fi = i;
        p.se = 50;
    } else if (i == 149 && 50 <= j && j < 100 && d == 1) { // w D
        d = 2; 
        p.fi = 150 + (j - 50);
        p.se = 49;
    } else if (150 <= i && i < 200 && j == 49 && d == 4) { // w F
        d = 3; 
        p.fi = 149;
        p.se = 50 + (i - 150);
    } else if (i == 150 && 0 <= j && j < 50 && d == 3) { // r F
        d = 3; 
        p.fi = 149;
        p.se = j;
    } else if (i == 149 && 0 <= j && j < 50  && d == 1) { // r E
        d = 1; 
        p.fi = 150;
        p.se = j;
    }

    if (g[p.fi][p.se] == 2) {
        p.fi = i;
        p.se = j;
        d = initiald;
        return true;
    }
    if (p.fi == i && p.se == j && d == initiald) {
        return false;
    } else {
        return true;
    };
}


void adv() {
    if (!border()) {
        int newi = p.fi + pi[d];
        int newj = p.se + pj[d];
        if (g[newi][newj] == 2) return;
        if (g[newi][newj] == 0) cout << "000!!!!!" << endl;
        p.fi = newi;
        p.se = newj;
    }
}



int main() {
    mread();
    cout << "(" << p.fi << ", " << p.se << ")" << endl;
    cout << "n: " << n << " m: " << m << endl;
    for (int in : ins) {
        if (in == L || in == R) {
            turn(in);
        } else {
            while (in--)
                adv();
        }
    } 
    int ans = 1000 * (p.fi+1) + 4*(p.se+1) + d;
    cout << "ans: " << ans << endl;
}
