#include <bits/stdc++.h>
using namespace std;

typedef struct HLine {
    int y;
    int x1;
    int x2;
    HLine(int y, int x1, int x2): y(y), x1(x1), x2(x2) {}
} HLine;

typedef struct VLine {
    int x;
    int y1;
    int y2;
    VLine(int x, int y1, int y2): x(x), y1(y1), y2(y2) {}
} VLine;

typedef struct DLine {
    int x1;
    int x2;
    int y1;
    int y2;
    DLine(int x1, int y1, int x2, int y2): x1(x1), y1(y1), x2(x2), y2(y2) {}
} DLine;

int main() {
    int x1, y1, x2, y2;
    vector<HLine> hs;
    vector<VLine> vs;
    vector<DLine> ds;
    while (scanf("%d,%d -> %d,%d\n", &x1, &y1, &x2, &y2) != EOF) {
        if (x1 == x2) {
            vs.push_back(VLine(x1, min(y1, y2), max(y1, y2))); 
        } else if (y1 == y2) {
            hs.push_back(HLine(y1, min(x1, x2), max(x1, x2))); 
        } else {
            ds.push_back(DLine(x1, y1, x2, y2)); 
        }
    }
    set<pair<int, int>> s;
    for (auto h : hs) {
        for (auto v : vs) {
            if ((v.y1 <= h.y && h.y <= v.y2) && (h.x1 <= v.x && v.x <= h.x2)) {
                s.insert({v.x,h.y});
            }
        }
    }
    for (int i=0; i<hs.size(); i++) {
        for (int j=0; j<hs.size(); j++) {
            if (i == j) continue;
            auto h1 = hs[i];
            auto h2 = hs[j];
            if (h1.y != h2.y) continue;
            if (h1.x1 <= h2.x1 && h2.x1 <= h1.x2) {
                for (int x=h2.x1; x<=min(h1.x2, h2.x2); x++) {
                    s.insert({x, h1.y});
                }
            }
        }
    }
    for (int i=0; i<vs.size(); i++) {
        for (int j=0; j<vs.size(); j++) {
            if (i == j) continue;
            auto v1 = vs[i];
            auto v2 = vs[j];
            if (v1.x != v2.x) continue;
            if (v1.y1 <= v2.y1 && v2.y1 <= v1.y2) {
                for (int y=v2.y1; y<=min(v1.y2, v2.y2); y++) {
                    s.insert({v1.x, y});
                }
            }
        }
    }

    for (int i=0; i<ds.size(); i++) {
        auto d = ds[i];
        int ps = abs(d.x2 - d.x1);
        int xdir = (d.x1 < d.x2) ? 1 : -1;
        int ydir = (d.y1 < d.y2) ? 1 : -1;
        for (int z=0; z<=ps; z++) {
            int x = d.x1 + z*xdir;
            int y = d.y1 + z*ydir;
            for (int j=0; j<ds.size(); j++) {
                if (i == j) continue;
                auto d1 = ds[j];
                int ps1 = abs(d1.x2 - d1.x1);
                int xdir1 = (d1.x1 < d1.x2) ? 1 : -1;
                int ydir1 = (d1.y1 < d1.y2) ? 1 : -1;
                for (int z1=0; z1<=ps1; z1++) {
                    int x1 = d1.x1 + z1*xdir1;
                    int y1 = d1.y1 + z1*ydir1;

                    if (x == x1 && y == y1) {
                        s.insert({x, y});
                    }
                }
            }

            for (auto h : hs) {
                if (y == h.y && h.x1 <= x && x <= h.x2) {
                    s.insert({x, y});
                }
            }
            for (auto v : vs) {
                if (x == v.x && v.y1 <= y && y <= v.y2) {
                    s.insert({x, y});
                }
            }
        }
    }

    cout << s.size() << endl;
}
