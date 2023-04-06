#include <bits/stdc++.h>
using namespace std;

typedef struct Dir {
    string name;
    int tsize;
    Dir* parent;
    map<string, Dir*> subdirs;
    map<string, int> files;

    Dir(string name): tsize(-1), name(name), parent(nullptr) {}

    void addfile(string fn, int fs) {
        files[fn] = fs;
    }

    void addsubdir(string dn, Dir* d) {
        subdirs[dn] = d;
    }

    void addp(Dir* p) {
        parent = p;
    }

    int ctsize() { // call till the end
        if (tsize != -1) return tsize;
        tsize = 0;
        for (auto& x : files) {
            tsize+=x.second;
        }
        for (auto& x : subdirs) {
            tsize+=x.second->ctsize();
        }
        return tsize;
    }
} Dir;

void getans(Dir* root, int& ans, int room) {
    if (root->tsize >= room) {
        ans=min(ans, root->tsize);
    }
    for (auto x : root->subdirs) {
        getans(x.second, ans, room);
    }
}

int main() {
    string l;
    Dir* root = new Dir("/");
    root->addp(root);
    int depth = 0;
    Dir* cd;
    while (getline(cin, l)) {
        if (l[0] == '$') {
            if (l.substr(2, 2) == "cd") {
                string dirname = l.substr(5, (int)l.size() - 5);
                if (dirname == "..") {
                    depth--;
                    cd = cd->parent;
                    if (cd == nullptr) {
                        cout << "!!!" << endl;
                    }
                } else if (dirname == "/") {
                    cd = root;        
                    depth = 0;
                } else {
                    depth++;
                    cd = cd->subdirs[dirname];
                }
            } else if (l.substr(2, 2) == "ls") {
                ;
            }
        } else if (l[0] == 'd') {
            string dirname = l.substr(4, l.size() - 4);
            if (cd->subdirs.count(dirname) == 0) {
                Dir* nd = new Dir(dirname);
                nd->addp(cd);
                cd->addsubdir(dirname, nd);
            }
        } else { // num
            int space = l.find(' ');
            int fsize = stoi(l.substr(0, space + 1));
            string fname = l.substr(space+1, l.size() - (space + 1));
            cd->addfile(fname, fsize);
            cout << "file: " << fname << " size: " << fsize << endl;
        }
    }
    int ATMOST = 100000;
    root->ctsize();

    int DISKSPACE = 70000000;
    int NEEDEDSPACE = 30000000;

    int frees = DISKSPACE - root->tsize;
    int room = NEEDEDSPACE - frees;
    
    int ans = 1e8;
    getans(root, ans, room);
    cout << ans << endl;
}
