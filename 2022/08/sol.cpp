#include <bits/stdc++.h>
using namespace std;

vector<int> nei = {-1, 0, 1, 0};
vector<int> nej = {0, 1, 0, -1};


int main() {
    string l;
    vector<vector<int>> grid;
    while (getline(cin, l)) {
        int n = l.size();
        vector<int> v(n);
        for (int i=0; i<n; i++) {
            v[i] = l[i] - '0';
        }
        grid.push_back(v);
    }

    int n = grid.size();
    int m = grid[0].size();

    int ms = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            int sc = 1;
            if (i == 0 || i == n-1 || j == 0 || j == m-1) {
                sc = 0;
            } else {
                for (int z=0; z<4; z++) {
                    int lsc = 0;
                    int newi = i + nei[z];
                    int newj = j + nej[z];
                    while (newi >= 0 && newi < n && newj >= 0 && newj < m) {
                        if (grid[newi][newj] < grid[i][j]) lsc++;
                        else if (grid[newi][newj] == grid[i][j]) {
                            lsc++;
                            break;
                        }
                        else break;
                        newi = newi + nei[z];
                        newj = newj + nej[z];
                    
                    }
                    sc *= lsc;
                }
                ms = max(ms, sc);
            }
        } 
    }
    cout << ms << endl;
}
