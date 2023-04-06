#include <bits/stdc++.h>
using namespace std;

int main() {
    int d;
    int prev = -1;
    int count = 0;
    while (cin >> d) {
        if (prev != -1 && d > prev) {
            count++;
        }
        prev = d;
    }
    cout << count << endl;
}
