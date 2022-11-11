#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = (int)1e9 + 7;

int main() {
  ios_base::sync_with_stdio(0),cin.tie(0);
  int n; cin >> n;
  vector<vector<int> > trap(n + 1, vector<int>(n + 1, 0));
  vector<vector<int> > dp = trap;
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    for (int j = 0; j < n; j++) {
      trap[i + 1][j + 1] = s[j] == '*';
    }
  }
  if (trap[1][1]) {
    cout << "0\n";
    exit(0);
  }

  dp[1][1] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == 1 && j == 1) continue;
      if (!trap[i][j]) {
        dp[i][j] = ((trap[i - 1][j] ? 0 : dp[i - 1][j]) + (trap[i][j - 1] ? 0 : dp[i][j - 1])) % M;;
      }
    }
  }
  cout << dp[n][n] << '\n';
}
