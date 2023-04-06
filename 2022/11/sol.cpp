#include <bits/stdc++.h>
using namespace std;

const int MX = 10;
vector<long long> ms[MX];

long long ws(int i, long long old) {
    if (i == 0) return ((old * 5)%9699690);
    if (i == 1) return ((old + 5)%9699690);
    if (i == 2) return ((old * 19)%9699690);
    if (i == 3) return ((old + 7)%9699690);
    if (i == 4) return ((old + 2)%9699690);
    if (i == 5) return ((old + 1)%9699690);
    if (i == 6) return ((old * old)%9699690);
    if (i == 7) return ((old + 4)%9699690);
}

int ts(int i, long long old) {
    if (i == 0) return (ws(i, old) % 11 == 0) ? 6 : 5;
    if (i == 1) return (ws(i, old) % 19 == 0) ? 6 : 0;
    if (i == 2) return (ws(i, old)% 5 == 0) ? 3 : 1;
    if (i == 3) return (ws(i, old)% 3 == 0) ? 1 : 0;
    if (i == 4) return (ws(i, old)% 13 == 0) ? 2 : 7;
    if (i == 5) return (ws(i, old)% 17 == 0) ? 4 : 7;
    if (i == 6) return (ws(i, old)% 7 == 0) ? 5 : 4;
    if (i == 7) return (ws(i, old)% 2 == 0) ? 3 : 2;
}

int main() {
    ms[0].push_back(73); 
    ms[0].push_back(77);
    
    ms[1].push_back(57); 
    ms[1].push_back(88);
    ms[1].push_back(80);
    
    ms[2].push_back(61); 
    ms[2].push_back(81);
    ms[2].push_back(84);
    ms[2].push_back(69); 
    ms[2].push_back(77);
    ms[2].push_back(88);
    
    ms[3].push_back(78); 
    ms[3].push_back(89);
    ms[3].push_back(71);
    ms[3].push_back(60); 
    ms[3].push_back(81);
    ms[3].push_back(84);
    ms[3].push_back(87);
    ms[3].push_back(75);

    ms[4] = {60, 76, 90, 63, 86, 87, 89};
    ms[5] = {88};
    ms[6] = {84, 98, 78, 85};
    ms[7] = {98, 89, 78, 73, 71};

    vector<int> ins (8);

    for (int r=1; r<10002; r++) {
        for (int m = 0; m<8; m++) {
            for (auto x : ms[m]) {
                ins[m]++;
                long long nw = ws(m, x);
                int j=ts(m, x);
                ms[j].push_back(nw);
            }   
            ms[m].clear(); 
        } 
        if (r == 10000) {
            vector<int> inscp(ins);
            sort(inscp.begin(), inscp.end());
            long long ans = 1;
            ans *= (long long)inscp.back() * inscp[6];
            cout << ans << endl;
        } 
    }
}
