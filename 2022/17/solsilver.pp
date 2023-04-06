#include <bits/stdc++.h>
using namespace std;

const int W = 7;
const int N = 1e6;
vector<vector<vector<int>>> shapes(5);
vector<vector<int>> g(N, vector<int>(W, 0));

int wi(int r) {
    return shapes[r][0].size();
}
int he(int r) {
    return shapes[r].size();
}

bool coli(int r, int i, int j) {
    for (int ii=i; ii<i+he(r); ii++) {
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
    for (int k=0; k<2022; k++) { // keep rocks comming
        int r = k % 5;

        int i = top - 3 - he(r);
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
    }
    cout << N - 1 - top << endl;
}
