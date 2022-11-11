#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,avx")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int INF = (int)1e8;

int main() {
  int n; cin >> n;
  vector<int> a(n+1);
  for (int i = 1; i <= n; i++) cin >> a[i];

  vector<int> p{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
  int p_len = p.size();
  vector<int> fac(60);
  for (int i = 0; i < p_len; i++) {
    for (int j = p[i]; j < 60; j += p[i]) fac[j] |= (1<<i);
  }
  vector<vector<int>> dp(n+1, vector<int>((1 << p_len), INF));
  vector<vector<int>> best(n+1, vector<int>((1 << p_len), -1));

  dp[0][0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (1<<p_len); j++) {
      for (int k = 1; k < 60; k++) if ((j & fac[k]) == 0) {
        int val = dp[i][j] + abs(a[i+1] - k);
        if (dp[i+1][j | fac[k]] > val) {
          dp[i+1][j | fac[k]] = val;
          best[i+1][j | fac[k]] = k;
        }
      }
    }
  }

  vector<int> ans(n+1);
  int best_idx = -1, best_val = INF;
  for (int j = 0; j < (1<<p_len); j++) if (dp[n][j] < best_val) {
    best_val = dp[n][j];
    best_idx = j;
  }
  for (int i = n; i >= 1; i--) {
    auto k = best[i][best_idx];
    ans[i] = k;
    best_idx ^= fac[k];
  }

  for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
}
