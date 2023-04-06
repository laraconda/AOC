#include <bits/stdc++.h>
using namespace std;

int main() {
    string l;
    int X = 1;
    int c = 1;
    int ans = 0;
    queue<pair<int, int>> q;
    int te = 244;
    bool busy = false;
    vector<vector<char>> crt(6, vector<char>(40, '.'));
    while (te--) {
        if (!q.empty()) {
            auto qf = q.front();
            if (qf.first == c) {
                X+=qf.second;
                q.pop();
                busy = false;
            }
        }
        if (c == 20 || c == 60 || c == 100 || c == 140 || c == 180 || c == 220) {
            ans+=c*X;
        }
        if (!busy && getline(cin, l)) {
            if (l[0] == 'a') {
                int x = stoi(l.substr(5, l.size() - 5)); 
                q.push({c+2, x});
                busy = true;
            } else {
                ; 
            }
        }
        int i = (c-1) / 40;
        int j = (c-1) % 40;
        if (X == j)
            crt[i][j] = '#';
        else if (X-1 == j && X-1 >= 0)
            crt[i][X-1] = '#';
        else if (X+1 == j && X+1 < 40)
            crt[i][X+1] = '#';
        c++;
    }

    for (int i=0; i<6; i++) {
        for (int j=0; j<40; j++) {
            cout << crt[i][j];
        }
        cout << endl;
    }

    cout << ans << endl;
}
