#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  ll ans = -1e9, sum = 0;
  for (int i = 0; i < n; i++) {
    sum += v[i];
    ans = max(ans, sum);
    if (sum < 0) sum = 0;
  }
  cout << ans << '\n';
}
