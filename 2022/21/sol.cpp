#include <bits/stdc++.h>
using namespace std;

typedef double dou;
const double INF = 1e9;

typedef struct ope {
    string a;
    string b;
    string s;
    dou dp;

    ope(string a, string b, string s): a(a), b(b), s(s), dp(INF){}
    ope(dou dp): a(""), b(""), s("!"), dp(dp) {}
    ope(): a(""), b(""), s(""), dp(-7) {}
} ope;

map<string, ope> m;
dou eval(ope& o) {
    // if (o.dp != INF) return o.dp;
    if (o.s == "+") o.dp = eval(m[o.a]) + eval(m[o.b]);
    if (o.s == "-") o.dp = eval(m[o.a]) - eval(m[o.b]);
    if (o.s == "*") o.dp = eval(m[o.a]) * eval(m[o.b]);
    if (o.s == "/") o.dp = eval(m[o.a]) / eval(m[o.b]);
    return o.dp;
}

void mread() {
    string l;
    while (getline(cin, l)) {
        stringstream ss(l);
        string name;
        ss >> name;
        name.pop_back();
        if (l.size() >= 16) {
            string a, sign, b;
            ss >> a >> sign >> b;
            m[name] = ope(a,b,sign);
        } else {
            dou ai;
            ss >> ai;
            m[name] = ope(ai);
        }
    }
}

int main() {
    cout.precision(20);
    mread();
    dou l = 0;
    dou h = 1e18;
    dou tar = 8226036122233;
    while (l < h) {
        dou cand = l + (h - l)/2;
        m["humn"] = ope(cand);
        dou e = eval(m["qntq"]);
        cout << "cand: "<< cand <<" e: " << e << endl;
        cout << "diff: " << e - tar << endl;
        if (e < tar) {
            h = cand; 
        } else if (e > tar){
            l = cand; 
        } else {
            cout << "ans: " << cand << endl;
        }
    }
}
