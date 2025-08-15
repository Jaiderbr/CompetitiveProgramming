/*
add: https://github.com/Jaiderbr/CompetitiveProgramming/blob/main/String/aho%20corasick.cpp
You want to select as many non-overlapping substrings of S
as possible such that each selected substring is exactly equal to one of the M strings.

3
7 2
arwhwar
ar
w
7 1
arwhwar
ar
4 1
rrrr
rr

------
4
2
2


*/

void solve(){

    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<string> st(m);
    forn(i, m) cin >> st[i];

    aho_corasick aho(st); 
    vector<pair<int, int>> intervals;
    int cur = 0;

    forn(i, n) {
        cur = aho.get_suffix_link(cur, s[i]);
        int dict_node = aho.nodes[cur].word_index < 0 ? aho.nodes[cur].dict : cur;

        while (dict_node >= 0) {
            int widx = aho.nodes[dict_node].word_index;
            int len = st[widx].size();
            intervals.pb({i - len + 1, i}); 
            dict_node = aho.nodes[dict_node].dict;
        }
    }

    sort(all(intervals), [](auto &a, auto &b) {
        if (a.s == b.s) return a.f < b.f;
        return a.s < b.s;
    });

    int ans = 0, last_end = -1;
    each(it, intervals) {
        if (it.f > last_end) {
            ans++;
            last_end = it.s;
        }
    }

    cout << ans << endl;
}  
