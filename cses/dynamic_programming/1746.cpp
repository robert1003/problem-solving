#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = (int)1e9 + 7;
const int N = (int)1e5 + 5;

ll dp[N][105];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, m; cin >> n >> m;
  vector<int> v(n + 1);
  for (int i = 1; i <= n; i++) cin >> v[i];
    
  if (v[1])
    dp[1][v[1]] = 1;
  else
    fill(dp[1], dp[1] + m + 1, 1);

  for (int i = 2; i <= n; i++) {
    if (v[i])
      for (int j = max(1, v[i] - 1); j <= min(m, v[i] + 1); j++)
        dp[i][v[i]] = (dp[i][v[i]] + dp[i - 1][j]) % M;
    else {
      for (int j = 1; j <= m; j++) {
        for (int k = max(1, j - 1); k <= min(m, j + 1); k++)
          dp[i][j] = (dp[i][j] + dp[i - 1][k]) % M;
      }
    }
  }

  int ans = 0;
  for (int j = 1; j <= m; j++) ans = (ans + dp[n][j]) % M;
  cout << ans << '\n';
}
