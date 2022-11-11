#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int x, n;
  cin >> x >> n;
  vector<int> p(n);
  for (int i = 0; i < n; i++) cin >> p[i];
  vector<int> pp = p;
  sort(pp.begin(), pp.end());
  map<int, int> id;
  for (int i = 0; i < n; i++) id[pp[i]] = i;


  vector<int> fa(n + 1), sz(n + 1);
  for (int i = 0; i <= n; i++) {
    fa[i] = i;
    if (i == 0) sz[i] = pp[0];
    else if (i == n) sz[i] = x - pp[n - 1];
    else sz[i] = pp[i] - pp[i - 1];
  }
  function<int(int)> find = [&](int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
  };
  auto merge = [&](int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (sz[u] < sz[v]) swap(u, v);
    fa[v] = u;
    sz[u] += sz[v];
    sz[v] = 0;
  };

  int cur = max(pp[0], x - pp[n - 1]);
  for (int i = 1; i < n; i++) {
    cur = max(cur, pp[i] - pp[i - 1]);
  }
  vector<int> ans = {cur};
  for (int i = n - 1; i >= 0; i--) {
    int curid = id[p[i]];
    merge(curid, curid + 1);
    cur = max(cur, sz[find(curid)]);
    ans.push_back(cur);
  }
  reverse(ans.begin(), ans.end());
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
}
