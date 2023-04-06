#include <bits/stdc++.h>
using namespace std;

// Thought that maybe a star would work but there
// are many incopatibilities


typedef pair<int,int> pii;

const int N = 30;
const int M = 125;
vector<vector<int>> g(N, vector<int>(M, 0));

priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater> q;
set<pii> open;
set<pii> closed;
map<pii, int> d;

vector<int> ni = {-1, 0, 1, 0};
vector<int> nj = {0, 1, 0, -1};


int md(pii a, pii b) {
    return abs(a.first - b.first) + abs(a.second - b.second); 
}

int astar(pii start, pii end) {
    open.insert(start);
    q.push({md(start, end), start});
    d[start] = 0;
    while (!open.empty()) {
        auto x = q.top(); q.pop();
        auto pos = x.second;
        auto f = x.first;
        if (pos.first == end.first && pos.second == end.second) {
            ;
        } else {
            for (int z=0; z<4; z++) {
                int newi = i + ni[z];
                int newj = j + nj[z];
                if (newi < 1 || newi >= 26 || newj < 1 || newj >= 121) continue;
                if (g[newi][newj] > 0) continue;
                int cost = d[pos] + 1;
                auto ij = {newi, newj};
                if (open.count(ij) > 0) {
                    if (d[ij] <= cost) continue;
                } else if (closed.count({newi, newj}) > 0) {
                    if (d[ij] <= cost) continue;
                    closed.erase(ij);
                    open.insert(ij);
                    int newf = cost + md(end, ij);
                    q.push({newf, ij});
                } else {
                    open.insert(ij);
                    int newf = cost + md(end, ij);
                    q.push({newf, ij});
                }
            } 
            closed.inser(pos);
        }
    }
}


void sim() {
    ;
}

int main() {
    string l;
    int n = 0;
    while (getline(cin, l)) {
            
    }
    cout << n << endl;
}
