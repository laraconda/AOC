#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<map<int, vector<int>>> plans;

void mread() {
    string l;
    while (getline(cin, l)) {
        stringstream ss(l);
        int orecost;
        int claycost;
        int obscostore;
        int obscostclay;
        int geocostore;
        int geocostobs;
        string trash;
        for (int i=0; i<6; i++)
            ss >> trash; 
        ss >> orecost;
        for (int i=0; i<5; i++)
            ss >> trash; 
        ss >> claycost; 
        for (int i=0; i<5; i++)
            ss >> trash; 
        ss >> obscostore;
        for (int i=0; i<2; i++)
            ss >> trash; 
        ss >> obscostclay;
        for (int i=0; i<5; i++)
            ss >> trash; 
        ss >> geocostore;
        for (int i=0; i<2; i++)
            ss >> trash; 
        ss >> geocostobs;

        map<int, vector<int>> plan;
        plan[0] = {orecost};
        plan[1] = {claycost};
        plan[2] = {obscostore, obscostclay};
        plan[3] = {geocostore, geocostobs};
        plans.push_back(plan);
        cout << orecost << ", " << claycost << ", " << obscostore << " & " << obscostclay << ", " << geocostore << " & " << geocostobs << endl;
    }
}


void buildr(int pi, int name, int& ore, int& clay, int& obs, int& bore, int& bclay, int& bobs, int& bgeo) {
    auto plan = plans[pi];
    auto v = plan[name];
    if (name == 0 || name == 1) {
        ore -= v[0];
        if (name == 0) bore++;
        else if (name == 1) bclay++;
    } else if (name == 2) {
        ore -= v[0];
        clay -= v[1];
        bobs++;
    } else if (name == 3) {
        ore -= v[0];
        obs -= v[1];
        bgeo++;
    }
}

bool pc(int pi, int name, int ore, int clay, int obs) {
    auto plan = plans[pi];
    auto v = plan[name];
    if (name == 0) {
        return (ore >= v[0]);
    } else if (name == 1) {
        return (ore >= v[0]);
    } else if (name == 2) {
        return (ore >= v[0] && clay >= v[1]);
    } else if (name == 3) {
        return (ore >= v[0] && obs >= v[1]);
    }
    return false;
}

void col(int& ore, int& clay, int& obs, int& geo, int bore, int bclay, int bobs, int bgeo, int mins) {
    ore += bore*mins;
    clay += bclay*mins;
    obs += bobs*mins;
    geo += bgeo*mins;
}


map<ll, int> dp;

ll makestate(int& ore, int& clay, int& obs, int& geo, int& bore, int& bclay, int& bobs, int& bgeo, int& ms) {
    ll state = 0;
    return (((((((((state << 9 | ore) << 8 | clay) << 8 | obs) << 5 | bore) << 5 | bclay) << 5 | bobs) << 5 | bgeo) << 5 | ms) << 8 | geo);
}


int maxres(int name, int pi) {
    auto plan = plans[pi];
    if (name == 0) {
        return max(max(max(plan[0][0], plan[1][0]), plan[2][0]), plan[3][0]);
    }
    if (name == 1) {
        return plan[2][1]; 
    }
    if (name == 2)
        return plan[3][1];
}

vector<int> whenbot(int ore, int clay, int obs, int bore, int bclay, int bobs, int pi) {
    vector<int> ts(4, -1);
    for (int i=0; i<4; i++) {
        for (int t=0; t<27; t++) {
            if (pc(pi, i, ore+bore*t, clay+bclay*t, 
            obs+bobs*t)) {
                ts[i] = t+1;
                break;
            }
        }
    }
    return ts;
}


int rec(int name, int ore, int clay, int obs, int geo, int bore, int bclay, int bobs, int bgeo, int ms, int pi, int tnbf) {
    col(ore,clay,obs,geo,bore,bclay,bobs,bgeo,tnbf);
    buildr(pi,name,ore,clay,obs,bore,bclay,bobs,bgeo);
    if (ms == 0) return geo;
    if (maxres(0,pi) < bore) return geo;
    if (maxres(1,pi) < bclay) return geo;
    if (maxres(2,pi) < bobs) return geo;
    ll state = makestate(ore,clay,obs,geo,bore,bclay,bobs,bgeo,ms);
    if (dp.count(state)) return dp[state];
    
    int an = -1;
    vector<int> ts = whenbot(ore,clay,obs,bore,bclay,bobs,pi);
    for (int i =0; i<4; i++) {
        int tnb = ts[i];
        if (tnb == -1) continue;
        if (ms - tnb < 0) tnb = ms; // go to 0
        int nms = ms - tnb;
                 
        an=max(an,rec(i,ore,clay,obs,geo,bore,bclay,bobs,bgeo,nms,pi,tnb)); 
    }
  
    return dp[state] = an;
}


int main() {
    mread(); 
    int ans = 1;
    int startmin = 32;
    cout << "mins: " << startmin << endl;
    for (int pi=0; pi<(int)plans.size(); pi++) {
        vector<int> ts = whenbot(0,0,0,1,0,0,pi);
        int ra = -1;
        for (int i=0; i<2; i++) {
            int r = rec(i,0,0,0,0,1,0,0,0,startmin - ts[i],pi,ts[i]);
            ra = max(r, ra);
        }
        ans *= ra;
        dp.clear();
    }
    cout << ans << endl;
}
