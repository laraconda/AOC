#include <bits/stdc++.h>
using namespace std;

void printgrid(vector<vector<vector<int>>>& grids, int b) {
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                cout << grids[b][i][j] << " ";
            }
            cout << endl;
        }
}

int checkwin(vector<vector<vector<int>>>& grids, set<int>& won) {
    int winner = -1;
    for (int b=0; b<grids.size(); b++) {
        if (won.count(b) > 0) continue;
        for (int i=0; i<5; i++) {
            int c = 0;
            for (int j=0; j<5; j++) {
                c += grids[b][i][j];
            }
            if (c == -5) {
                return b;
            }
        }
        for (int j=0; j<5; j++) {
            int c = 0;
            for (int i=0; i<5; i++) {
                c+=grids[b][i][j];
            }
            if (c == -5) {
                return b;
            }
        }
    }
    return winner;
}

int main() {
    vector<int> v = {69,88,67,56,53,97,46,29,37,51,3,93,92,78,41,22,45,66,13,82,2,7,52,40,18,70,32,95,89,64,84,68,83,26,43,0,61,36,57,34,80,39,6,63,72,98,21,54,23,28,65,16,76,11,20,33,96,4,10,25,30,19,90,24,55,91,15,8,71,99,58,14,60,48,44,17,47,85,74,87,86,27,42,38,81,79,94,73,12,5,77,35,9,62,50,31,49,59,75,1};

    vector<vector<vector<int>>> grids;
    int d;
    int j = 0;
    int i = 0;
    vector<vector<int>> grid(5, vector<int>(5));
    while (scanf("%d", &d) != EOF) {
        grid[i][j] = d;
        j++;
        if (j == 5) {
            j = 0;
            i++;
        }
        if (i == 5) {
            grids.push_back(grid);
            i = 0;
            j = 0;
        }
    }

    set<int> won;
    int lastval = -122;
    for (int& x : v) {
        for (int b=0; b<grids.size(); b++) {
            for (int i=0; i<5; i++) {
                for (int j=0; j<5; j++) {
                    if (grids[b][i][j] == x) {
                        grids[b][i][j] = -1;
                    }
                }
            }
        }

        int w = checkwin(grids, won);
        while (w != -1) {
            won.insert(w);
            int val = x;    
            int s = 0; 
            for (int i=0; i<5; i++) {
                for (int j=0; j<5; j++) {
                    if (grids[w][i][j] != -1) {
                        s += grids[w][i][j];
                    }
                }
            }
            val *= s;
            lastval = val;
            w = checkwin(grids, won);
        }
        cout << "lastval: " << lastval << " wsize: " << won.size() << endl;
    }
    cout << lastval << endl;
}
