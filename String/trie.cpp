// T.count pref(s) number of strings that have a as a prefix
struct trie {
    vector<vector<int>> to;
    vector<int> end, pref;
    int sigma; char norm;
    int lcpsum = 0;
    trie(int sigma_ = 26, char norm_ = 'a') : sigma(sigma_), norm(norm_) {
        to = { vector<int>(sigma) };
        end = { 0 }, pref = { 0 };
    }
    void insert(string s) {
        int x = 0;
        for (auto c : s) {
            int& nxt = to[x][c - norm];
            if (!nxt) {
                nxt = to.size();
                to.pb(vector<int>(sigma));
                end.pb(0), pref.pb(0);
            }
            // else lcpsum += pref[nxt];
            x = nxt, pref[x]++;
        }
        end[x]++, pref[0]++;
    }
    void erase(string s) {
        int x = 0;
        for (char c : s) {
            int& nxt = to[x][c - norm];
            x = nxt, pref[x]--;
            if (!pref[x]) nxt = 0;
        }
        end[x]--, pref[0]--;
    }
    int find(string s) {
        int x = 0;
        for (auto c : s) {
            x = to[x][c - norm];
            if (!x) return -1;
        }
        return x;
    }

    int count_pref(string s) {
        int id = find(s);
        return id >= 0 ? pref[id] : 0;
    }
};