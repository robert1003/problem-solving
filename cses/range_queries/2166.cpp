#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace segtree {
  vector<ll> a, tag;

  void push(int o) {
    if (tag[o]) {
      a[o] += tag[o];
      tag[o * 2 + 1] += tag[o];
      tag[o * 2 + 2] += tag[o];
      tag[o] = 0;
    }
  }
  void pull(int o) {
    a[o] = max(a[o * 2 + 1] + tag[o * 2 + 1], a[o * 2 + 2] + tag[o * 2 + 2]);
  }
  void build(int l, int r, vector<ll>& v, int o=0) {
    if (l + 1 == r) return void(a[o] = v[l]);
    int mid = (l + r) >> 1;
    build(l, mid, v, o * 2 + 1);
    build(mid, r, v, o * 2 + 2);
    pull(o);
  }
  void init(int n, vector<ll>& v) {
    a = vector<ll>(n * 4, 0);
    tag = vector<ll>(n * 4, 0);
    build(0, n, v);
  }
  void update(int l, int r, int ql, int qr, ll v, int o=0) {
    if (ql <= l && r <= qr) return void(tag[o] += v);
    int mid = (l + r) >> 1;
    push(o);
    if (qr <= mid) update(l, mid, ql, qr, v, o * 2 + 1);
    else if (mid <= ql) update(mid, r, ql, qr, v, o * 2 + 2);
    else {
      update(l, mid, ql, mid, v, o * 2 + 1);
      update(mid, r, mid, qr, v, o * 2 + 2);
    }
    pull(o);
  }
  ll query(int l, int r, int ql, int qr, int o=0) {
    if (ql <= l && r <= qr) return a[o] + tag[o];
    push(o);
    int mid = (l + r) >> 1;
    if (qr <= mid) return query(l, mid, ql, qr, o * 2 + 1);
    else if (mid <= ql) return query(mid, r, ql, qr, o * 2 + 2);
    else return max(query(l, mid, ql, mid, o * 2 + 1), query(mid, r, mid, qr, o * 2 + 2));
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<ll> v(n), pre(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  pre[0] = v[0];
  for (int i = 1; i < n; i++) pre[i] = pre[i - 1] + v[i];
  segtree::init(n, pre);
  for (int i = 0; i < q; i++) {
    int op, k, u, a, b; cin >> op;
    if (op == 1) {
      cin >> k >> u;
      segtree::update(0, n, k - 1, n, u - v[k - 1]);
      v[k - 1] = u;
    }
    else {
      cin >> a >> b; a--, b--;
      ll ans = segtree::query(0, n, a, b + 1);
      if (a > 0)
        ans -= segtree::query(0, n, a - 1, a);
      cout << max(0LL, ans) << '\n';
    }
  }
}
