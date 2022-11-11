#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace bit {
  vector<vector<int> > b;
  int n;

  void init(int _n) {
    n = _n;
    b = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
  }
  inline int lowbit(int x) {
    return x & (-x);
  }
  void update(int x, int y, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
      for (int j = y; j <= n; j += lowbit(j)) {
        b[i][j] += v;
      }
    }
  }
  int query(int x, int y) {
    if (x < 1 || y < 1) return 0;
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
      for (int j = y; j > 0; j -= lowbit(j)) {
        sum += b[i][j];
      }
    }
    return sum;
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<string> v(n);
  bit::init(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    for (int j = 0; j < n; j++) {
      if (v[i][j] == '*') bit::update(i + 1, j + 1, 1);
    }
  }
  for (int i = 0; i < q; i++) {
    int op; cin >> op;
    if (op == 1) {
      int x, y; cin >> x >> y; x--, y--;
      if (v[x][y] == '*') v[x][y] = '.', bit::update(x + 1, y + 1, -1);
      else v[x][y] = '*', bit::update(x + 1, y + 1, 1);
    }
    else {
      int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
      cout << bit::query(x2, y2) - bit::query(x1 - 1, y2) - bit::query(x2, y1 - 1) + bit::query(x1 - 1, y1 - 1) << '\n';
    }
  }
}
