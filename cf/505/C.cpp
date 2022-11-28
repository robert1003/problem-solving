#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, d; cin >> n >> d;
  vector<int> gem(30001, 0);
  for (int i = 0; i < n; i++) {
    int g; cin >> g; gem[g] += 1;
  }
  vector<vector<int>> dp(30001, vector<int>(491, 0));
  int offset = d - 245;
  for (int i = 30000; i >= 0; i--) {
    for (int j = max(1, d-245); j <= min(30000, d+245); j++) {
      for (int l = -1; l <= 1; l++) {
        if (i+(j+l) > 0 && i+(j+l) <= 30000 && j+l >= d-245 && j+l <= d+245) dp[i][j-offset] = max(dp[i][j-offset], dp[i+j+l][j+l-offset]);
      }
      dp[i][j-offset] += gem[i];
    }
  }

  cout << dp[d][d-offset] << '\n';
}
