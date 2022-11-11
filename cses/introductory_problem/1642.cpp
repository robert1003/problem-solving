#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, x; cin >> n >> x;
  vector<array<int, 2> > v(n);
  for (int i = 0; i < n; i++) cin >> v[i][0], v[i][1] = i;
  sort(v.begin(), v.end());
  map<int, array<int, 2> > sum;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      sum[v[i][0] + v[j][0]] = {v[i][1], v[j][1]};
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int residual = x - v[i][0] - v[j][0];
      auto it = sum.find(residual);
      if (it == sum.end()) continue;
      if (it->second[0] == v[i][1] || it->second[0] == v[j][1]) continue;
      if (it->second[1] == v[i][1] || it->second[1] == v[j][1]) continue;
      cout << v[i][1] + 1 << ' ' << v[j][1] + 1 << ' ' << it->second[0] + 1 << ' ' << it->second[1] + 1 << '\n';
      return 0;
    }
  }

  cout << "IMPOSSIBLE\n";
}
