#include <bits/stdc++.h>
using namespace std;

int main() {
    int ans = 0;
    string l;
    while (getline(cin, l)) {
        int n = l.size();
        int icomma = l.find(',');
        string A = l.substr(0, icomma);
        string B = l.substr(icomma + 1, n - icomma);

        int idash = A.find('-');
        n = A.size();
        string AA = A.substr(0, idash);
        string AB = A.substr(idash + 1, n - idash);
        
        idash = B.find('-');
        n = B.size();
        string BA = B.substr(0, idash);
        string BB = B.substr(idash + 1, n - idash);

        int aa = stoi(AA);
        int ab = stoi(AB);
        int ba = stoi(BA);
        int bb = stoi(BB);

        if ((aa <= ba && bb <= ab) || (ba <= aa && ab <= bb))
            ans++;
        else if (ba <= ab && ab <= bb)
            ans++;
        else if (aa <= bb && bb <= ab)
            ans++;
    }
    cout << ans << endl;
}
