#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace segtree {
  struct Node {
    ll lmax, mmax, rmax;
    ll sum;
  };

  Node merge(Node l, Node r) {
    Node o;
    o.sum = l.sum + r.sum;
    o.lmax = max(l.lmax, l.sum + r.lmax);
    o.mmax = max(l.rmax + r.lmax, max(l.mmax, r.mmax));
    o.rmax = max(r.rmax, r.sum + l.rmax);
    return o;
  };
  
  vector<Node> a;

  void pull(int o) {
    a[o] = merge(a[o * 2 + 1], a[o * 2 + 2]);
  }
  void build(int l, int r, vector<ll>& v, int o=0) {
    if (l + 1 == r) return void(a[o] = {v[l], v[l], v[l], v[l]});
    int mid = (l + r) / 2;
    build(l, mid, v, o * 2 + 1);
    build(mid, r, v, o * 2 + 2);
    pull(o);
  }
  void init(int n, vector<ll>& v) {
    a.resize(n * 4);
    build(0, n, v);
  }
  void update(int l, int r, int q, ll v, int o=0) {
    if (l + 1 == r) return void(a[o] = {v, v, v, v});
    int mid = (l + r) / 2;
    if (q < mid) update(l, mid, q, v, o * 2 + 1);
    else update(mid, r, q, v, o * 2 + 2);
    pull(o);
  }
  Node query(int l, int r, int ql, int qr, int o=0) {
    if (ql <= l && r <= qr) return a[o];
    int mid = (l + r) / 2;
    if (qr <= mid) return query(l, mid, ql, qr, o * 2 + 1);
    else if (mid <= ql) return query(mid, r, ql, qr, o * 2 + 2);
    else return merge(query(l, mid, ql, mid, o * 2 + 1), query(mid, r, mid, qr, o * 2 + 2));
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, m; cin >> n >> m;
  vector<ll> x(n);
  for (int i = 0; i < n; i++) cin >> x[i];
  segtree::init(n, x);
  for (int i = 0; i < m; i++) {
    int k, v; cin >> k >> v; k--;
    segtree::update(0, n, k, v);
    cout << max(0LL, segtree::query(0, n, 0, n).mmax) << '\n';
  }
}
