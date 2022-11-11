#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = (int)1e6 + 5;

int dp[N];

int DP(int x) {
  if (dp[x] >= 0) return dp[x];
  if (x == 0) return dp[x] = 0;
  dp[x] = (int)1e7;
  int _x = x;
  while (_x > 0) {
    dp[x] = min(dp[x], DP(x - (_x % 10)) + 1);
    _x /= 10;
  }
  return dp[x];
}

int main() {
  int n; cin >> n;
  fill(dp, dp + N, -1);
  cout << DP(n) << '\n';
}
