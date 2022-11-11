#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<array<int, 2> > v(n);
  for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
  sort(v.begin(), v.end());
  ll cur = 0, award = 0;
  for (auto [a, d] : v) {
    cur += a;
    award += d - cur;
  }
  cout << award << '\n';
}
