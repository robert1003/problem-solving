#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace bit {
  int n;
  vector<ll> b;

  void init(int _n) {
    n = _n;
    b.resize(n + 1);
    fill(b.begin(), b.end(), 0);
  }
  inline int lowbit(int x) { return x & (-x); }
  void upd(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i))
      b[i] += v;
  }
  ll qry(int x) {
    if (x <= 0) return 0;
    ll sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
      sum += b[i];
    return sum;
  }
  ll range_qry(int l, int r) {
    return qry(r) - qry(l - 1);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  bit::init(n);
  for (int i = 1; i <= n; i++) {
    int v; cin >> v;
    bit::upd(i, v);
  }
  while (q--) {
    int op, a, b; cin >> op >> a >> b;
    if (op == 1)
      bit::upd(a, b - bit::range_qry(a, a));
    else
      cout << bit::range_qry(a, b) << '\n';
  }
}
