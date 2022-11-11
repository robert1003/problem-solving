#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int k, n; cin >> n >> k;
  vector<array<int, 2> > v(n);
  vector<int> x;
  for (int i = 0; i < n; i++) {
    cin >> v[i][0] >> v[i][1];
    x.push_back(v[i][0]);
    x.push_back(v[i][1]);
  }
  sort(x.begin(), x.end());
  x.resize(unique(x.begin(), x.end()) - x.begin());
  for (int i = 0; i < n; i++) {
    v[i][0] = lower_bound(x.begin(), x.end(), v[i][0]) - x.begin() + 1;
    v[i][1] = lower_bound(x.begin(), x.end(), v[i][1]) - x.begin() + 1;
    cerr << i << ' ' << v[i][0] << ' ' << v[i][1] << '\n';
  }

  vector<array<int, 2> > op(x.size() + 1, array<int, 2>{0, 0});
  for (int i = 0; i < n; i++) {
    op[v[i][0]][0]++;
    op[v[i][1]][1]++;
  }

  int ans = n, cur = 0;
  for (int i = 1; i <= (int)x.size(); i++) {
    int diff = op[i][0] - op[i][1];
    if (cur + diff > k && diff > 0) {
      cerr << i << ' ' << cur << ' ' << diff << '\n';
      ans -= max(cur + diff - k, diff);
    }
    cur = max(cur + diff, k);
  }
  cout << ans << '\n';
}
