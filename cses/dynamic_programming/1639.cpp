#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  string s, t; cin >> s >> t;
  int n = (int)s.size(), m = (int)t.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  for (int i = 1; i <= n; i++) dp[i][0] = i;
  for (int j = 1; j <= m; j++) dp[0][j] = j;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
      if (s[i - 1] == t[j - 1])
        dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
      else
        dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
    }
  }
  cout << dp[n][m] << '\n';
}
