#include <bits/stdc++.h>
using namespace std;

int main() {
    string l;
    int ans  = 0;
    while (getline(cin, l)) {
        int x= l.find('|');
        string pa = l.substr(0, x-1);
        string pb = l.substr(x+2, l.size() - (x+2));
        int c = 0;
        for (int i=0; i<pb.size(); i++) {
            if (pb[i] == ' ') {
                if (c == 2 || c == 3 || c == 7 || c == 4) {
                    ans++; 
                } 
                c = 0;
            } else c++;
        }
        if (c == 2 || c == 3 || c == 7 || c == 4) {
            ans++; 
        }
    }
    cout << ans << endl;
}
