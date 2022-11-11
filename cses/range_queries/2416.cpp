#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace segtree {
#define mid (l + r) >> 1
#define lson o * 2 + 1
#define rson o * 2 + 2
  vector<ll> a, tag, len;

  void push(int o) {
    if (tag[o]) {
      a[o] += tag[o] * len[o];
      tag[lson] += tag[o];
      tag[rson] += tag[o];
      tag[o] = 0;
    }
  }
  void pull(int o) {
    a[o] = a[lson] + tag[lson] * len[lson] + a[rson] + tag[rson] * len[rson];
  }
  void build(int l, int r, vector<ll>& v, int o=0) {
    tag[o] = 0; len[o] = r - l;
    if (l + 1 == r) return void(a[o] = v[l]);
    build(l, mid, v, lson); build(mid, r, v, rson);
    pull(o);
  }
  void init(int n, vector<ll>& v) {
    a.resize(n * 4);
    tag.resize(n * 4);
    len.resize(n * 4);
    build(1, n + 1, v);
  }
  void update(int l, int r, int ql, int qr, ll v, int o=0) {
    if (ql <= l && r <= qr) return void(tag[o] += v);
    push(o);
    if (qr <= mid) update(l, mid, ql, qr, v, lson);
    else if (mid <= ql) update(mid, r, ql, qr, v, rson);
    else {
      update(l, mid, ql, mid, v, lson);
      update(mid, r, mid, qr, v, rson);
    }
    pull(o);
  }
  ll query(int l, int r, int ql, int qr, int o=0) {
    if (ql <= l && r <= qr) return a[o] + tag[o] * len[o];
    push(o);
    if (qr <= mid) return query(l, mid, ql, qr, lson);
    else if (mid <= ql) return query(mid, r, ql, qr, rson);
    else return query(l, mid, ql, mid, lson) + query(mid, r, mid, qr, rson);
  }
  void _print(int l, int r, int o=0) {
    cerr << l << ' ' << r << ' ' << a[o] << ' ' << tag[o] << '\n';
    if (l + 1 == r) return;
    _print(l, mid, lson);
    _print(mid, r, rson);
  }
  void print(int n) {
//    for (int i = 1; i <= n; i++)
//      cerr << query(1, n + 1, i, i + 1) << " \n"[i == n];
    _print(1, n + 1);
  }
}

vector<pair<int, int> > qs[200005];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<ll> v(n + 1), nv(n + 1);
  for (int i = 0; i < n; i++) {
    cin >> v[i + 1];
    nv[i + 1] = -v[i + 1];
  }
  for (int i = 0; i < q; i++) {
    int l, r; cin >> l >> r;
    qs[l].emplace_back(r, i);
  }
  segtree::init(n, nv);

  vector<ll> ans(q), val;
  deque<ll> dq;
  for (int i = n; i >= 1; i--) {
    // update
    while (!dq.empty() && v[dq.front()] <= v[i]) {
      int last = dq.front(); dq.pop_front();
      int rig = (dq.empty() ? n + 1 : dq.front());
      segtree::update(1, n + 1, last, rig, -v[last]);
    }
    int rig = (dq.empty() ? n + 1 : dq.front());
    segtree::update(1, n + 1, i, rig, v[i]);
    dq.push_front(i);
    
    // query
    for (auto [r, idx] : qs[i]) {
      ans[idx] = segtree::query(1, n + 1, i, r + 1);
    }

  }

  for (auto i : ans) cout << i << '\n';
}
