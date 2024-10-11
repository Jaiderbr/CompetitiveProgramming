/*
Given two arrays a and b of n non-negative integers, count the number of good pairs
l,r (1<=l<=r<=n), satisfying F(l,r)<G(l,r)
Where F(l,r) is the sum of the square of numbers in the range [l,r]
And G(l,r) is the square of the bitwise OR of the range [l,r]
*/

main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    // brute();
    int n; cin >> n;
    vector<int> a(n), b(n), prefix(n + 6);
    set<int> pro[25];
    forn(i, n) cin >> a[i];
    forn(i, n) cin >> b[i];
    forn(init, 22) pro[init].insert(n);
    forn(i, n) prefix[i + 1] = prefix[i] + a[i] * a[i];
    prefix.erase(prefix.begin());
    forn(i, n) forn(j, 22) if (b[i] & (1 << j)) pro[j].insert(i);
 
    int ans = 0;
    forn(i, n) {
        int last = i, Or = b[i];
        while (last < n) {
            int best = n;
            forn(j, 22) {
                if (!(Or & (1 << j))) best = min(best, *pro[j].upper_bound(last));
            }
            int l = last, r = best - 1, x = -1, need = Or * Or;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (prefix[mid] - (i > 0 ? prefix[i - 1] : 0) >= need) r = mid - 1;
                else l = mid + 1, x = mid;
            }
            if (~x) ans += x - last + 1;
            swap(last, best);
            if (last < n) Or |= b[last];
        }
    }
    cout << ans << endl;
 
 
    cout << flush;
    return 0;
}
