#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, x; cin >> n >> x;
  vector<int> h(n), s(n);
  for (int i = 0; i < n; i++) cin >> h[i];
  for (int i = 0; i < n; i++) cin >> s[i];
  vector<int> dp(x + 1, 0);
  for (int j = 0; j < n; j++) {
    for (int i = x; i >= h[j]; i--)
      dp[i] = max(dp[i], dp[i - h[j]] + s[j]);
  }
  cout << dp[x] << '\n';
}
