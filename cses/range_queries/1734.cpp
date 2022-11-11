#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<int> v(n + 1), x;
  for (int i = 1; i <= n; i++) cin >> v[i], x.push_back(v[i]);
  sort(x.begin(), x.end());
  x.resize(unique(x.begin(), x.end()) - x.begin());
  for (int i = 1; i <= n; i++) v[i] = lower_bound(x.begin(), x.end(), v[i]) - x.begin();

  vector<int> ans(q);
  vector<array<int, 4>> query;
  ll sqN = (ll)sqrt(n + 1);
  for (int i = 0; i < q; i++) {
    int a, b; cin >> a >> b;
    query.push_back({a, b, i, a / sqN});
  }
  sort(query.begin(), query.end(), [&](auto a, auto b) { return a[3] < b[3] || (a[3] == b[3] && a[1] < b[1]);  });

  vector<int> cnt(x.size());
  int cur = 0;

  auto inc = [&](int x) {
    if (!cnt[x])
      cur++;
    cnt[x]++;
  };
  auto dec = [&](int x) {
    cnt[x]--;
    if (!cnt[x])
      cur--;
  };

  for (int i = 0, l = 1, r = 0; i < q; i++) {
    auto [ql, qr, idx, _] = query[i];
    while (l < ql) dec(v[l++]);
    while (l > ql) inc(v[--l]);
    while (r < qr) inc(v[++r]);
    while (r > qr) dec(v[r--]);
    ans[idx] = cur;
  }

  for (int i = 0; i < q; i++) cout << ans[i] << '\n';
}
