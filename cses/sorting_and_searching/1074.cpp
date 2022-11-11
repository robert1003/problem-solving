#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  sort(v.begin(), v.end());

  auto getcost = [&](int x) {
    ll cost = 0;
    for (int i = 0; i < n; i++) cost += abs(v[i] - x);
    return cost;
  };

  if (n % 2) cout << getcost(v[n/2]) << '\n';
  else cout << min(getcost(v[n/2]), getcost(v[n/2-1])) << '\n';
}
