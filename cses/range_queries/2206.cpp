#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Segtree {
  vector<ll> a;

  void pull(int o) {
    a[o] = min(a[o * 2 + 1], a[o * 2 + 2]);
  }
  void build(int l, int r, vector<ll>& v, int o=0) {
    if (l + 1 == r) return void(a[o] = v[l]);
    int mid = (l + r) / 2;
    build(l, mid, v, o * 2 + 1);
    build(mid, r, v, o * 2 + 2);
    pull(o);
  }
  void init(int n, vector<ll>& v) {
    a = vector<ll>(n * 4, 0);
    build(0, n, v);
  }
  void update(int l, int r, int q, int v, int o=0) {
    if (l + 1 == r) return void(a[o] += v);
    int mid = (l + r) / 2;
    if (q < mid)
      update(l, mid, q, v, o * 2 + 1);
    else
      update(mid, r, q, v, o * 2 + 2);
    pull(o);
  }
  ll query(int l, int r, int ql, int qr, int o=0) {
    if (ql <= l && r <= qr) return a[o];
    int mid = (l + r) / 2;
    if (qr <= mid)
      return query(l, mid, ql, qr, o * 2 + 1);
    else if (mid <= ql)
      return query(mid, qr, ql, qr, o * 2 + 2);
    else {
      auto a1 = query(l, mid, ql, mid, o * 2 + 1);
      auto a2 = query(mid, r, mid, qr, o * 2 + 2);
      return min(a1, a2);
    }
  }
} segtree[2];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<ll> v[2], p(n);
  v[0].resize(n);
  v[1].resize(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    v[0][i] = p[i] - i;
    v[1][i] = p[i] + i;
  }
  segtree[0].init(n, v[0]);
  segtree[1].init(n, v[1]);

  for (int i = 0; i < q; i++) {
    int op; cin >> op;
    if (op == 1) {
      int k, x; cin >> k >> x; k--;
      segtree[0].update(0, n, k, x - p[k]);
      segtree[1].update(0, n, k, x - p[k]);
      p[k] = x;
    }
    else {
      int k; cin >> k; k--;
      cout << min(segtree[0].query(0, n, 0, k + 1) + k, segtree[1].query(0, n, k, n) - k) << '\n';
    }
  }
}
