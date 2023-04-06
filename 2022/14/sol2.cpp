/* trying to solve the problem but typing fast.
    Attempt 1: 52:47
        Fucked the reading and kept thinking the wrong part was the simulation
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e3;

int main () {
    vector<vector<int>> grid(N, vector<int>(N, 0));
    string l;
    while (getline(cin, l)) {
        int x;
        int y;
        pair<int, int> prev = {-1, -1};
        stringstream ss(l);
        while (ss >> x) {
            ss.ignore(1);
            ss >> y;
            ss.ignore(4);
            if (prev.first != -1) {
                int x1 = min(x, prev.first);
                int x2 = max(x, prev.first);
                int y1= min(y, prev.second);
                int y2= max(y, prev.second);
                for (int x=x1; x <= x2; x++) {
                    for (int y=y1; y<=y2; y++) {
                       grid[x][y] = 1;
                       cout << x << "," << y<< " => ";
                    }
                }
            }
            prev = {x, y};
        }
        cout << "endl" << endl;
    }

    bool mvoid = false;
    vector<int> nx = {0, -1, 1};
    vector<int> ny = {1, 1, 1};
    int ans = 0;
    while (!mvoid) {
        int x = 500;
        int y = 0;
        bool moved = true;
        ans++;
        while (moved && !mvoid) {
            moved = false;
            for (int z=0; z<3; z++) {
                int newx = x + nx[z];
                int newy = y + ny[z];
                if (newx >= 0 && !moved && grid[newx][newy] == 0) {
                    moved = true;
                    x = newx;
                    y = newy;
                    if (y > 800) {
                        mvoid = true;
                        break;
                    }
                }
            } 
            if (!moved) {
                cout << "static" << endl;
                grid[x][y] = 1;
            }
        }
    }
    cout << "ans: " << ans-1 << endl;

}
