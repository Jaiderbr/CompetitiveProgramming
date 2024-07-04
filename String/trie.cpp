struct Node {
    int cont;
    Node* child[26];
};

struct Trie {
    Node* root;

    Trie() {
        root = new Node();
    }

    void insert(const string& s) {
        Node* curr = root;
        for (int i = 0; i < sz(s); ++i) {
            if (curr->child[s[i] - 'a'] == NULL) {
                curr->child[s[i] - 'a'] = new Node();
            }
            curr->child[s[i] - 'a']->cont++;
            curr = curr->child[s[i] - 'a'];

        }
    }
    void remove(const string& s) {
        Node* curr = root;
        for (int i = 0; i < sz(s); ++i) {
            if (curr->child[s[i] - 'a'] == NULL) {
                return;
            }
            curr->child[s[i] - 'a']->cont--;
            curr = curr->child[s[i] - 'a'];
        }
    }
    int calc(const string& s) {
        auto node = root;
        vector<int> c;
        for (int i = 0; i < sz(s); i++) {
            node = node->child[s[i] - 'a'];
            c.push_back(node->cont);
        }
        int ans = c[sz(s) - 1] * sz(s);
        for (int i = sz(s) - 2; i >= 0; i--) {
            ans += (c[i] - c[i + 1]) * (i + 1);
        }
        return ans;
    }

    pair<int, int> query(const string& s) {
        Node* curr = root;
        for (int i = 0; i < sz(s); ++i) {
            if (curr->child[s[i] - 'a'] == NULL) {
                return make_pair(i, curr->cont);
            }
            curr = curr->child[s[i] - 'a'];
        }
        return make_pair(sz(s), curr->cont);
    }
};
