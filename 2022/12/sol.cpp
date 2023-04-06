#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    string l;
    vector<vector<char>> grid;
    vector<pair<int, int>> sts;
    pair<int, int> ed;
    int li = 0;
    while (getline(cin, l)) {
        int n = l.size();
        vector<char> v(n);
        for (int i=0; i<n;i++) {
            if (l[i] == 'S' || l[i] == 'a') {
                v[i] = 'a';
                sts.push_back({li,i});
            } else if (l[i] == 'E') {
                v[i] = 'z';
                ed = make_pair(li,i);
            } else {
                v[i] = l[i];
            }
        }
        grid.push_back(v);
        li++;
    }

    int n = grid.size();
    int m = grid[0].size();

    vector<int> nei = {-1, 0, 1, 0};
    vector<int> nej = {0, 1, 0, -1};

    int ans = INF; 
    for (auto st : sts) {
        vector<vector<int>> ds(n, vector<int>(m, INF));
        queue<pair<int, int>> q({st});
        ds[st.first][st.second] = 0;
        while (!q.empty()) {
            auto x = q.front(); q.pop();
            int i = x.first;
            int j = x.second;
            for (int z=0; z<4; z++) {
                int newi = i + nei[z];
                int newj = j + nej[z];
                if (newi < 0 || newj < 0 || newi >= n || newj >= m) continue;
                if (grid[newi][newj] - 'a' > (grid[i][j] - 'a') + 1 ||
                ds[newi][newj] != INF) {
                    continue;
                }
                q.push({newi, newj});
                ds[newi][newj] = ds[i][j] + 1;
            }
        }
        ans = min(ans, ds[ed.first][ed.second]);
    }
    cout << ans << endl;

}
