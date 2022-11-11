#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = (int)1e9 + 7;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, x; cin >> n >> x;
  vector<int> c(n + 1);
  for (int i = 1; i <= n; i++) cin >> c[i];
  sort(c.begin() + 1, c.end());
  vector<ll> dp(x + 1);
  dp[0] = 1;
  for (int j = 1; j <= n; j++) {
    for (int i = 0; i <= x; i++) {
      //dp[i][j] = dp[i][j - 1];
      if (i >= c[j]) dp[i] = (dp[i] + dp[i - c[j]]) % M;
      //dp[i][j] = (dp[i][j] + dp[i - c[j]][j]) % M;
    }
  }
  cout << dp[x] << '\n';
}
