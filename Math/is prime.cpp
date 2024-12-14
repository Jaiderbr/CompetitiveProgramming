bool is_prime(int64_t n) {
    if (n < 2) return 0;
    for (int64_t p = 2; p * p <= n; p += p % 2 + 1) if (n % p == 0) return 0;
    return 1;
}
