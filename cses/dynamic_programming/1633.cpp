#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = (int)1e9 + 7;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<int> dp(n + 1);
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = i - 1; j >= max(0, i - 6); j--)
      dp[i] = (dp[i] + dp[j]) % M;
  }
  cout << dp[n] << '\n';
}
