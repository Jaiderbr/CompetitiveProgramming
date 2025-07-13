void add(int x) {}
void del(int x) {}
int get_ans() {}

vector<int> mo(const vector<pair<int, int>>& q) {
  int l = 0, r = -1, blk = 350; // sqrt(n)
  vector<int> inx(sz(q)), ans(sz(q));
  auto K = [&](const pair<int, int>& x) -> pair<int, int> {
    return pair<int, int>(x.f / blk, x.s ^ -(x.f / blk & 1));
    };
  iota(all(inx), 0);
  sort(all(inx), [&](int a, int b) -> bool { return K(q[a]) < K(q[b]); });
  /*
  sort(all(inx), [&](int l, int r) {
      if (q[l].f / blk != q[r].f / blk) return q[l].f < q[r].f;
      if ((q[l].f / blk) % 2) return q[l].s > q[r].s;
      return q[l].s < q[r].s;
  });
  */
  for (int nxt : inx) {
    pair<int, int> it = q[nxt];
    while (r < it.s) add(++r);
    while (l > it.f) add(--l);
    while (r > it.s) del(r--);
    while (l < it.f) del(l++);
    ans[nxt] = get_ans();
  }
  return ans;
}