#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace bit {
  int n;
  vector<ll> b;

  void init(int _n) {
    n = _n;
    b.resize(n + 1);
  }
  inline int lowbit(int x) { return x & (-x); }
  void update(int x, ll v) {
    for (int i = x; i <= n; i += lowbit(i))
      b[i] += v;
  }
  ll query(int x) {
    ll sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
      sum += b[i];
    return sum;
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  bit::init(n);
  vector<int> v(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> v[i];
    bit::update(i, v[i] - v[i - 1]);
  }
  while (q--) {
    int op; cin >> op;
    if (op == 1) {
      int a, b, u; cin >> a >> b >> u;
      bit::update(b + 1, -u);
      bit::update(a, u);
    }
    else {
      int k; cin >> k;
      cout << bit::query(k) << '\n';
    }
  }
}
