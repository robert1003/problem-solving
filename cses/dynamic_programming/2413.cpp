#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = (int)1e6 + 5;
const int M = (int)1e9 + 7;

ll dp[N][2];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  dp[1][0] = dp[1][1] = 1;
  for (int i = 1; i < N - 1; i++) {
    dp[i + 1][0] = (dp[i + 1][0] + dp[i][0] * 2 + dp[i][1] * 1) % M;
    dp[i + 1][1] = (dp[i + 1][1] + dp[i][0] * 1 + dp[i][1] * 4) % M;
  }
  int t, n; cin >> t;
  while (t--) {
    cin >> n;
    cout << (dp[n][0] + dp[n][1]) % M << '\n';
  }
}
