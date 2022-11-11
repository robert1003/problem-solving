#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace segtree {
  vector<vector<int>> a;
  int n;

  void pullx(int x, int y) {
    a[x][y] = a[x * 2 + 1][y] + a[x * 2 + 2][y];
  }
  void pully(int x, int y) {
    a[x][y] = a[x][y * 2 + 1] + a[x][y * 2 + 2];
  }
  void init(int _n) {
    n = _n;
    a = vector<vector<int>>(n * 4, vector<int>(n * 4, 0));
  }
  void updatey(int x, int last, int l, int r, int q, int v, int y=0) {
    if (l + 1 == r) {
      if (last)
        return void(a[x][y] += v);
      else
        return void(pullx(x, y));
    }
    int mid = (l + r) / 2;
    if (q < mid) updatey(x, last, l, mid, q, v, y * 2 + 1);
    else updatey(x, last, mid, r, q, v, y * 2 + 2);
    pully(x, y);
  }
  void update(int l, int r, int qx, int qy, int v, int x=0) {
    if (l + 1 == r) return void(updatey(x, 1, 0, n, qy, v));
    int mid = (l + r) / 2;
    if (qx < mid) update(l, mid, qx, qy, v, x * 2 + 1);
    else update(mid, r, qx, qy, v, x * 2 + 2);
    updatey(x, 0, 0, n, qy, v);
  }
  int queryy(int x, int l, int r, int ql, int qr, int y=0) {
    if (ql <= l && r <= qr) return a[x][y];
    int mid = (l + r) / 2;
    if (qr <= mid) return queryy(x, l, mid, ql, qr, y * 2 + 1);
    else if (mid <= ql) return queryy(x, mid, r, ql, qr, y * 2 + 2);
    else {
      return queryy(x, l, mid, ql, mid, y * 2 + 1) + queryy(x, mid, r, mid, qr, y * 2 + 2);
    }
  }
  int query(int l, int r, int qlx, int qrx, int qly, int qry, int x=0) {
    if (qlx <= l && r <= qrx) return queryy(x, 0, n, qly, qry);
    int mid = (l + r) / 2;
    if (qrx <= mid) return query(l, mid, qlx, qrx, qly, qry, x * 2 + 1);
    else if (mid <= qlx) return query(mid, r, qlx, qrx, qly, qry, x * 2 + 2);
    else {
      return query(l, mid, qlx, mid, qly, qry, x * 2 + 1) + query(mid, r, mid, qrx, qly, qry, x * 2 + 2);
    }
  }
  void printy(int x, int l, int r, int y=0) {
    cerr << ' ' << l << ' ' << r << ' ' << a[x][y] << '\n';
    if (l + 1 == r) return;
    int mid = (l + r) / 2;
    printy(x, l, mid, y * 2 + 1);
    printy(x, mid, r, y * 2 + 2);
  }
  void print(int l, int r, int x=0) {
    cerr << l << ' ' << r << '\n';
    printy(x, 0, n);
    if (l + 1 == r) return;
    int mid = (l + r) / 2;
    print(l, mid, x * 2 + 1);
    print(mid, r, x * 2 + 2);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<string> v(n);
  segtree::init(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    for (int j = 0; j < n; j++) {
      if (v[i][j] == '*') segtree::update(0, n, i, j, 1);
    }
  }
  for (int i = 0; i < q; i++) {
    int op; cin >> op;
    if (op == 1) {
      int x, y; cin >> x >> y; x--, y--;
      if (v[x][y] == '*') v[x][y] = '.', segtree::update(0, n, x, y, -1);
      else v[x][y] = '*', segtree::update(0, n, x, y, 1);
    }
    else {
      int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
      cout << segtree::query(0, n, x1-1, x2, y1-1, y2) << '\n';
    }
  }
}
