#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace segtree {
  vector<int> data;

  void pull(int o) {
    data[o] = min(data[o * 2 + 1], data[o * 2 + 2]);
  }
  void build(int l, int r, vector<int>& v, int o=0) {
    if (l + 1 == r) return void(data[o] = v[l]);
    int mid = (l + r) / 2;
    build(l, mid, v, o * 2 + 1);
    build(mid, r, v, o * 2 + 2);
    pull(o);
  }
  void init(int n, vector<int>& v) {
    data.resize(n * 4);
    build(0, n, v);
  }
  void update(int l, int r, int q, int v, int o=0) {
    if (l + 1 == r) return void(data[o] = v);
    int mid = (l + r) / 2;
    if (q < mid) update(l, mid, q, v, o * 2 + 1);
    else update(mid, r, q, v, o * 2 + 2);
    pull(o);
  }
  int query(int l, int r, int ql, int qr, int o=0) {
    if (ql <= l && r <= qr) return data[o];
    int mid = (l + r) / 2;
    if (qr <= mid) return query(l, mid, ql, qr, o * 2 + 1);
    else if (mid <= ql) return query(mid, r, ql, qr, o * 2 + 2);
    else return min(query(l, mid, ql, mid, o * 2 + 1), query(mid, r, mid, qr, o * 2 + 2));
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  segtree::init(n, v);
  while (q--) {
    int op, a, b; cin >> op >> a >> b;
    if (op == 1) {
      segtree::update(0, n, a - 1, b);
    }
    else {
      cout << segtree::query(0, n, a - 1, b) << '\n';
    }
  }
}
