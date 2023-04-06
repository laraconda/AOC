#include <bits/stdc++.h>
using namespace std;

int main() {
    string l;
    long long s = 0;
    while(getline(cin, l)) {
        char x = l[0];
        char y = l[2];
        if (x == 'A') { // rock
            if (y == 'Y') { // draw
                s+=3;
                s+=1;
            } else if (y == 'X') { // lose
                s+=3;
            } else { // win
                s+= 6;
                s+= 2;
            }
        } else if (x == 'B') { // paper
            if (y == 'Y') {
                s+=3;
                s+=2;
            } else if (y == 'X') {
                s+= 1;
            } else {
                s+= 6;
                s+=3;
            }
        } else { // scissors
            if (y == 'Y') {
                s+=3;
                s+=3;
            } else if (y == 'X') {
                s+=2;
            } else {
                s+=6;
                s+=1;
            }
        }
    }
    cout << s << endl;
}
