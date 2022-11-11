#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, x; cin >> n >> x;
  vector<int> c(n + 1);
  for (int i = 1; i <= n; i++) cin >> c[i];
  vector<ll> dp(x + 1, (ll)1e7);
  dp[0] = 0;
  for (int i = 1; i <= n; i++) if (c[i] <= x) dp[c[i]] = 1;
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= n; j++) {
      if (i >= c[j]) dp[i] = min(dp[i], dp[i - c[j]] + 1);
    }
  }
  cout << (dp[x] <= (ll)1e6 ? dp[x] : -1) << '\n';
}
