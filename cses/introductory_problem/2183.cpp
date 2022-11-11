#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  sort(v.begin(), v.end());
  if (v[0] > 1) {
    cout << "1\n";
  }
  else {
    ll r = 1;
    for (int i = 1; i < n; i++) {
      ll l = min(v[i], 1 + v[i]);
      if (l - r > 1) break;
      r += v[i];
    }
    cout << r + 1 << '\n';
  }
}
