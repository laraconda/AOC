#include <bits/stdc++.h>
using namespace std;

const int C = 23;
vector<vector<vector<int>>> m(C, vector<vector<int>>(C, vector<int>(C, 0)));
int ma=-1;

void mread() {
    int x,z,y;
    string l;
    while(getline(cin, l)){
    stringstream ss(l);
        while (ss >> x) {
            ss.ignore(1);
            ss >> y;
            ss.ignore(1);
            ss >> z;
            m[x+1][y+1][z+1] = 1;    

            if (x > ma) ma = x;
            if (y > ma) ma = y;
            if (z > ma) ma = z;
        }
        cout << x<<","<<y<<","<<z<<endl;
    }
    ma++;
    cout << "ma: " << ma << endl;
}

int main() {
    mread(); 

    vector<int> xne = {1, 0,-1,0,0, 0};
    vector<int> yne = {0, 0, 0,0,1,-1};
    vector<int> zne = {0,-1, 0,1,0, 0};

    int ans=0;

    for (int x=1; x<=ma; x++) {
        for (int y=1; y<=ma; y++) {
            for (int z=1; z<=ma; z++) {
                if (m[x][y][z]) {
                    cout << "cube at: " << x << "," << y <<","<<z<<endl;
                    for (int ne=0; ne<6; ne++) {
                        int nx = x + xne[ne];        
                        int ny = y + yne[ne];        
                        int nz = z + zne[ne];
                        if (!m[nx][ny][nz]) {
                            ans++;
                            cout << "no cube at: " << x << "," << y <<","<<z<<endl;
                        }
                    }
                }
            }
        }
    }
    cout << ans << endl;
}
