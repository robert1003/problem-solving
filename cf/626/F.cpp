#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll M = (ll)1e9+7;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, k; cin >> n >> k;
  vector<int> a(n+1);
  for (int i = 1; i <= n; i++) cin >> a[i];
  sort(a.begin(), a.end());
  vector<vector<vector<ll>>> dp(2, vector<vector<ll>>(n+1, vector<ll>(k+1, 0)));

  dp[1][1][0] = 1;
  dp[1][0][0] = 1;
  int cur = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < n+1; j++)
      fill(dp[cur^1][j].begin(), dp[cur^1][j].end(), 0);
    for (int j = 0; j <= i; j++) {
      for (int l = 0; l <= k; l++) {
        int val = l + j * (a[i+1] - a[i]);
        if (val > k) continue;
        if (dp[cur][j][l] == 0) continue;
        // new group & close new group immediately
        dp[cur^1][j][val] = (dp[cur^1][j][val] + dp[cur][j][l]) % M;
        // add to one group
        dp[cur^1][j][val] = (dp[cur^1][j][val] + dp[cur][j][l]*j) % M;
        // close one group
        if (j > 0)
          dp[cur^1][j-1][val] = (dp[cur^1][j-1][val] + dp[cur][j][l]*j) % M;
        // new open group
        dp[cur^1][j+1][val] = (dp[cur^1][j+1][val] + dp[cur][j][l]) % M;
      }
    }
    cur ^= 1;
  }

  ll ans = 0;
  for (int i = 0; i <= k; i++) ans = (ans + dp[cur][0][i]) % M;
  cout << ans << '\n';
}
