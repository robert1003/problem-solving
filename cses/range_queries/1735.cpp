#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace segtree {
#define mid (l + r) >> 1
#define lson o * 2 + 1
#define rson o * 2 + 2
  vector<ll> sum, len, tag[2];

  void pull(int o) {
    sum[o] = tag[0][o] = tag[1][o] = 0;
    sum[o] += (tag[0][lson] ? tag[0][lson] * len[lson] : sum[lson]) + tag[1][lson] * len[lson];
    sum[o] += (tag[0][rson] ? tag[0][rson] * len[rson] : sum[rson]) + tag[1][rson] * len[rson];
  }
  void push(int o) {
    sum[o] = (tag[0][o] ? tag[0][o] * len[o] : sum[o]) + tag[1][o] * len[o];
    if (tag[0][o]) {
      tag[0][lson] = tag[0][o], tag[1][lson] = 0;
      tag[0][rson] = tag[0][o], tag[1][rson] = 0;
      tag[0][o] = 0;
    }
    if (tag[1][o]) {
      tag[1][lson] += tag[1][o];
      tag[1][rson] += tag[1][o];
      tag[1][o] = 0;
    }
  }
  void build(int l, int r, vector<ll>& v, int o=0) {
    len[o] = r - l;
    tag[0][o] = tag[1][o] = 0;
    if (l + 1 == r) {
      sum[o] = v[l];
      return;
    }
    build(l, mid, v, lson);
    build(mid, r, v, rson);
    pull(o);
  }
  void init(int n, vector<ll>& v) {
    sum.resize(n * 4);
    tag[0].resize(n * 4);
    tag[1].resize(n * 4);
    len.resize(n * 4);
    build(0, n, v);
  }
  void inc(int l, int r, int ql, int qr, int v, int o=0) {
    if (ql <= l && r <= qr) return void(tag[1][o] += v);
    push(o);
    if (qr <= mid) inc(l, mid, ql, qr, v, lson);
    else if (mid <= ql) inc(mid, r, ql, qr, v, rson);
    else {
      inc(l, mid, ql, mid, v, lson);
      inc(mid, r, mid, qr, v, rson);
    }
    pull(o);
  }
  void upd(int l, int r, int ql, int qr, int v, int o=0) {
    if (ql <= l && r <= qr) {
      tag[0][o] = v,tag[1][o] = 0;
      return;
    }
    push(o);
    if (qr <= mid) upd(l, mid, ql, qr, v, lson);
    else if (mid <= ql) upd(mid, r, ql, qr, v, rson);
    else {
      upd(l, mid, ql, mid, v, lson);
      upd(mid, r, mid, qr, v, rson);
    }
    pull(o);
  }
  ll qry(int l, int r, int ql, int qr, int o=0) {
    if (ql <= l && r <= qr) return (tag[0][o] ? tag[0][o] * len[o] : sum[o]) + tag[1][o] * len[o];
    push(o);
    if (qr <= mid) return qry(l, mid, ql, qr, lson);
    else if (mid <= ql) return qry(mid, r, ql, qr, rson);
    else {
      return qry(l, mid, ql, mid, lson) + qry(mid, r, mid, qr, rson);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<ll> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  segtree::init(n, v);
  for (int i = 0; i < q; i++) {
    int op, l, r, v; cin >> op;
    if (op == 1) {
      cin >> l >> r >> v;
      segtree::inc(0, n, l-1, r, v);
    }
    else if (op == 2) {
      cin >> l >> r >> v;
      segtree::upd(0, n, l-1, r, v);
    }
    else {
      cin >> l >> r;
      cout << segtree::qry(0, n, l-1, r) << '\n';
    }
  }
}
