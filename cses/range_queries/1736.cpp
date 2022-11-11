#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace segtree {
#define mid (l + r) >> 1
#define lson o * 2 + 1
#define rson o * 2 + 2
  vector<ll> sum, tag, diff, len;

  ll calc(int o) {
    ll a0 = tag[o], an = a0 + diff[o] * (len[o] - 1);
    return sum[o] + (a0 + an) * len[o] / 2;
  }
  void pull(int o) {
    assert(tag[o] == 0);
    sum[o] = calc(lson) + calc(rson);
  }
  void push(int o) {
    if (tag[o]) {
      sum[o] = calc(o);
      tag[lson] += tag[o]; diff[lson] += diff[o];
      tag[rson] += tag[o] + diff[o] * len[lson]; diff[rson] += diff[o];
      tag[o] = diff[o] = 0;
    }
  }
  void build(int l, int r, vector<ll>& v, int o=0) {
    tag[o] = diff[o] = 0, len[o] = r - l;
    if (l + 1 == r) return void(sum[o] = v[l]);
    build(l, mid, v, lson);
    build(mid, r, v, rson);
    pull(o);
  }
  void init(int n, vector<ll>& v) {
    sum.resize(n * 4);
    tag.resize(n * 4);
    len.resize(n * 4);
    diff.resize(n * 4);
    build(0, n, v);
  }
  void upd(int l, int r, int ql, int qr, int v, int o=0) {
    if (ql <= l && r <= qr) {
      tag[o] += v, diff[o]++;
      return;
    }
    push(o);
    if (qr <= mid) upd(l, mid, ql, qr, v, lson);
    else if (mid <= ql) upd(mid, r, ql, qr, v, rson);
    else {
      upd(l, mid, ql, mid, v, lson);
      upd(mid, r, mid, qr, v + (mid) - ql, rson);
    }
    pull(o);
  }
  ll qry(int l, int r, int ql, int qr, int o=0) {
    if (ql <= l && r <= qr) return calc(o);
    push(o);
    if (qr <= mid) return qry(l, mid, ql, qr, lson);
    else if (mid <= ql) return qry(mid, r, ql, qr, rson);
    else return qry(l, mid, ql, mid, lson) + qry(mid, r, mid, qr, rson);
  }
  void print(int l, int r, int o=0) {
    cerr << l << ' ' << r << ' ' << len[o] << ' ' << tag[o] << ' ' << diff[o] << ' ' << sum[o] << ' ' << calc(o) << '\n';
    if (l + 1 == r) return;
    print(l, mid, lson);
    print(mid, r, rson);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<ll> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  segtree::init(n, v);
  for (int i = 0; i < q; i++) {
    int op, l, r; cin >> op >> l >> r; l--, r--;
    if (op == 1)
      segtree::upd(0, n, l, r + 1, 1);
    else
      cout << segtree::qry(0, n, l, r + 1) << '\n';
  }
}
