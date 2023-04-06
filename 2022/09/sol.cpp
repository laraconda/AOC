#include <bits/stdc++.h>
using namespace std;

int main() {
    set<pair<int,int>> s;
    string l;
    vector<pair<int,int>> r(10, {0,0});
    s.insert({0,0});
    while (getline(cin, l)) {
        int steps = stoi(l.substr(2, l.size() - 2));
        while (steps--) {
            if (l[0] == 'U') {
                r[0].first -= 1;  
            } else if (l[0] == 'R') {
                r[0].second += 1;  
            } else if (l[0] == 'D') {
                r[0].first += 1;  
            } else if (l[0] == 'L') {
                r[0].second -= 1;  
            }
            for (int i=0; i<9; i++) {
                if ((abs(r[i].first - r[i+1].first) == 2 && abs(r[i].second - r[i+1].second) < 2) ||
                   (abs(r[i].second - r[i+1].second) == 2 && abs(r[i].first - r[i+1].first) < 2)) {
                    cout << "moving: " << i + 1 << endl;
                    if (r[i].first < r[i+1].first) {
                        r[i+1].first--;
                    } else if (r[i].first > r[i+1].first) {
                        r[i+1].first++;
                    }
                    if (r[i].second > r[i+1].second) {
                        r[i+1].second++;
                    } else if (r[i].second < r[i+1].second) {
                        r[i+1].second--;
                    }
                }
                if ((abs(r[i].first - r[i+1].first) == 2 && abs(r[i].second - r[i+1].second) == 2)) {
                    if (r[i].first < r[i+1].first) r[i+1].first--;
                    else r[i+1].first++;
                    if (r[i].second < r[i+1].second) r[i+1].second--;        
                    else r[i+1].second++;
                }
                if (i == 8)
                    s.insert(r[i+1]);
            }
        }
    }
    cout << s.size() << endl;
}
