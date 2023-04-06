#include <bits/stdc++.h>
using namespace std;

const int N = 1e3;

int main() {
    vector<vector<int>> grid(N, vector<int>(N, 0)); // 0 - ., 1 - #, 2 - sand 
    int x;
    int y;
    int lowy = -1;
    string l;
    while (getline(cin, l)) {
        stringstream ss(l);
        bool first = true;
        pair<int, int> prev;
        while (ss >> x) {
            ss.ignore(1);
            ss >> y;
            ss.ignore(4);
            grid[y][x] = 1;
            lowy = max(lowy, y);
            if (first) {
                first = false;
                prev = {y, x};
            } else {
                if (prev.first == y) {
                    for (int j=min(x, prev.second); j<=max(x, prev.second); j++) {
                        grid[y][j] = 1;
                    }
                } else {
                    for (int i=min(y, prev.first); i<=max(y, prev.first); i++) {
                        grid[i][x] = 1;
                    }
                } 
                prev = {y, x};
            }
        }
    }
    lowy +=2;
    for (int j=0; j<N; j++) {
        grid[lowy][j] = 1;
    }
    pair<int, int> startp = {0, 500};
    vector<int> mi = {1, 1, 1};
    vector<int> mj = {0, -1, 1};
    pair<int, int> sand = startp;
    int ans = 0;
    while (grid[0][500] == 0) {
        int i = sand.first;
        int j = sand.second;
        bool adv = true;
        bool lb = false;
        while (adv) {
            bool moved = false;
            for (int z=0; z<3; z++) {
                int newi = i + mi[z];
                int newj = j + mj[z];
                if (newi >= N || newj >= N) {
                    cout << "out of bounds" << endl;
                }
                if (newj >= 0 && !moved && grid[newi][newj] == 0) {
                    moved = true;
                    i = newi;
                    j = newj;
                }
                if (newj < 0) {
                    cout << "left bounds" << endl;
                    lb = true;
                }
            }
            if (!moved) {
                if (!lb) {
                    grid[i][j] = 2;
                    ans++;
                }
                adv = false;
            }
        }
        sand = startp;
    }
    cout << ans << endl;
}
