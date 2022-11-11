#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
using ll = long long;

const int N = (int)4e5 + 5;

namespace bit {
  int b[N], n;

  void init(int _n) {
    n = _n;
    fill(b, b + 1 + n, 0);
  }
  inline int lowbit(int x) {
    return x & (-x);
  }
  void add(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i))
      b[i] += v;
  }
  int qry(int x) {
    if (x <= 0) return 0;
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
      ans += b[i];
    return ans;
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<pair<pair<int, int>, int> > v(n);
  vector<int> x;
  for (int i = 0; i < n; i++) {
    cin >> v[i].F.F >> v[i].F.S;
    v[i].S = i;
    x.push_back(v[i].F.F);
    x.push_back(v[i].F.S);
  }
  sort(x.begin(), x.end());
  x.resize(unique(x.begin(), x.end()) - x.begin());
  for (int i = 0; i < n; i++) {
    v[i].F.F = lower_bound(x.begin(), x.end(), v[i].F.F) - x.begin() + 1;
    v[i].F.S = lower_bound(x.begin(), x.end(), v[i].F.S) - x.begin() + 1;
  }

  vector<vector<int> > ans(2, vector<int>(n, 0));

  sort(v.begin(), v.end(), [&](auto a, auto b) { return a.F.F < b.F.F || (a.F.F == b.F.F && a.F.S > b.F.S); });
  bit::init(x.size() + 1);
  for (auto [p, id] : v) {
    ans[1][id] = bit::qry(x.size()) - bit::qry(p.S - 1);
    bit::add(p.S, 1);
  }

  reverse(v.begin(), v.end());
  bit::init(x.size() + 1);
  for (auto [p, id] : v) {
    ans[0][id] = bit::qry(p.S);
    bit::add(p.S, 1);
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < n; j++) cout << bool(ans[i][j]) << " \n"[j == n - 1];
  }
}
