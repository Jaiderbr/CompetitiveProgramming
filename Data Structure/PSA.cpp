template<typename T>
struct PSA {
    //indexado en 1
    vector<T> arr;
    vector<T> nums;
    const T n;

    PSA(T n) : n(n), arr(1, 0) nums.resize(n + 1);
    void read() {
        for (int i = 1; i <= n; i++) cin >> nums[i];
        Build();
    }
    void Build() {
        for (int i = 1; i <= n; i++) arr.push_back(arr[i - 1] + nums[i]);
    }
    T query(T L, T R) { return arr[R] - arr[L - 1]; }
};
