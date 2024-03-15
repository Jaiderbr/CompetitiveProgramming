
struct Node {
    char data;
    int freq;
    Node* L, * R;
    Node(char data, int freq) : data(data), freq(freq), L(nullptr), R(nullptr) {}
};
struct Huffman {
    unordered_map<char, int> freqMap;
    unordered_map<char, string>hfCodes;
    string str;
    Node* root;
    Huffman(string& str) : str(str) {
        for (auto&& i : str) freqMap[i]++;
        root = build();
        createHF(root, "");
    }

    struct oper {
        bool operator()(const Node* L, const Node* R) const {
            return L->freq > R->freq;
        }
    };

    Node* build() {
        priority_queue<Node*, vector<Node*>, oper> pq;
        each(i, freqMap) {
            pq.push(new Node(i.f, i.s));
        }
        if (sz(pq) == 1) {
            Node* L = pq.top();
            pq.pop();
            Node* parent = new Node('\0', L->freq);
            parent->L = L;
            pq.push(parent);
        }
        while (sz(pq) > 1) {
            Node* L = pq.top();
            pq.pop();
            Node* R = pq.top();
            pq.pop();
            Node* parent = new Node('\0', L->freq + R->freq);
            parent->L = L;
            parent->R = R;
            pq.push(parent);
        }
        return pq.top();
    }

    void createHF(Node* root, string code) {
        if (root == nullptr) return;
        if (!root->L && !root->R) {
            hfCodes[root->data] = code;
        }
        createHF(root->L, code + "0");
        createHF(root->R, code + "1");
    }

    int LengthBinary() {
        int cnt = 0;
        for (auto&& i : str) cnt += sz(hfCodes[i]);
        return cnt;
    }
    void _print() {
        each(i, hfCodes) cout << i.f << ' ' << i.s << endl;
    }

};





int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);



    string s; cin >> s;
    Huffman hf(s);
    cout << hf.LengthBinary() << endl;

    // hf._print();





    cout << flush;
    return 0;
}

