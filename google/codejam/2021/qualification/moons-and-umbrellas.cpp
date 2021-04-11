#include <bits/stdc++.h>
using namespace std;

const int N = 1000 + 5;
const int inf = (int)1e6;

int x, y, dp[N][2]; // [0] for C, [1] for J
string s;

int DP() {
  int n = (int)s.size();
  dp[0][0] = (s[0] == 'C' ? 0 : inf);
  dp[0][1] = (s[0] == 'J' ? 0 : inf);
  for(int i = 1 ; i < n ; ++i) {
    dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + y);
    dp[i][1] = min(dp[i - 1][0] + x, dp[i - 1][1]);
    if(s[i] == 'C') dp[i][1] = inf;
    else if(s[i] == 'J') dp[i][0] = inf;
  }
  /*
  cerr << "DP:\n";
  for(int i = 1 ; i < n ; ++i) {
    cerr << i << ' ' << dp[i][0] << ' ' << dp[i][1] << '\n';
  }
  */

  return min(dp[n - 1][0], dp[n - 1][1]);
}

void init() {
  cin >> x >> y >> s;
}
void solve(int kase) {
  int ans = inf;
  if(s[0] == '?') {
    s[0] = 'C'; ans = min(ans, DP());
    s[0] = 'J'; ans = min(ans, DP());
  }
  else ans = min(ans, DP());
  cout << "Case #" << kase << ": " << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t, kase = 1; cin >> t;
  while(t--) {
    init();
    solve(kase++);
  }
}
