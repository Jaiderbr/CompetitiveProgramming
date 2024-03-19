string manacher(const string& s) {
    if (sz(s) > 0) {
        string curr = "";
        for (auto&& i : s) {
            curr += i;
            curr += "#";
        }
        curr = "@#" + curr + "&";
        vector<ll> pali(sz(curr), 0);
        ll bigCenter = 0;
        ll R = 0;
        for (ll i = 1; i < sz(curr) - 1; i++) {
            if (i < R) {
                ll opposite_to_i = 2 * bigCenter - i;
                pali[i] = min(pali[opposite_to_i], R - i);
            }
            while (curr[i + (pali[i] + 1)] == curr[i - (pali[i] + 1)]) {
                pali[i]++;
            }
            if (i + pali[i] > R) {
                bigCenter = i;
                R = i + pali[i];
            }
        }
        ll _HC = 0, _CI = 0;
        for (ll i = 1; i < sz(curr) - 1; i++) {
            if (pali[i] > _HC) {
                _HC = pali[i];
                _CI = i;
            }
        }

        string ans = "";
        if (_HC > 0) {
            ll start = _CI - _HC + 1;
            ll end = _CI + _HC - 1;
            for (ll i = start; i <= end; i += 2) {
                ans += curr[i];
            }
        }
        else {
            ans = s[0];
        }
        return ans;
    }
    else {
        return "";
    }
}