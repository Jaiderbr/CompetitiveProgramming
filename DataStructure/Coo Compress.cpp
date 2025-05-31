template<typename T>
struct COO_COMPRESS {
    vector<T> nums;
    bool is_compress = true;

    int size() {
        if (!is_compress) compress();
        return sz(nums);
    }

    void clear() {
        nums.clear();
        is_compress = true;
    }

    void insert(T x) {
        nums.pb(x);
        is_compress = false;
    }

    void compress() {
        sort(all(nums));
        nums.resize(unique(all(nums)) - nums.begin());
        is_compress = true;
    }

    vector<T> compress_offline(vector<T> nums) {
        if (!sz(nums))return nums;
        vector<pair<T, int>> vvv;
        forn(i, sz(nums)) vvv.pb({ nums[i],i });
        sort(all(vvv));
        int cont = 0;
        T last = vvv[0].first;
        nums[vvv[0].second] = 0;
        forne(i, 1, sz(vvv)) {
            if (vvv[i].first != last) cont++, last = vvv[i].first;
            nums[vvv[i].second] = cont;
        }
        return nums;
    }

    int get(T x) {
        if (!is_compress) compress();
        int pos = lower_bound(all(nums), x) - nums.begin();
        assert(pos != sz(nums) && nums[pos] == x);
        return pos;
    }

    T iget(int x) {
        if (!is_compress) compress();
        assert(0 <= x && x < sz(nums));
        return nums[x];
    }
};
