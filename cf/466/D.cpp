#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = (ll)1e9 + 7;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, h; cin >> n >> h;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<vector<ll>> dp(n, vector<ll>(2000, 0));

  if (a[0] - h < -1 || a[0] - h > 0) {
    cout << "0\n";
    return 0;
  } else if (a[0] - h == -1) {
    dp[0][0] = dp[0][1] = 1;
  } else { // a[0] == h
    dp[0][0] = 1;
  }

  for (int i = 1; i < n; i++) {
    if (a[i] > h) {
      cout << "0\n";
      return 0;
    }
    if (a[i] == h)
      dp[i][0] = dp[i-1][0];
    else {
      // [], ][, ]
      dp[i][h-a[i]-1] = (dp[i-1][h-a[i]-1]*(1+h-a[i]-1)%mod + dp[i-1][h-a[i]]*(h-a[i])%mod) % mod;
      // [, -
      dp[i][h-a[i]] = (dp[i-1][h-a[i]-1] + dp[i-1][h-a[i]]) % mod;
    }
  }

  cout << dp[n-1][0] << '\n';
}
