#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<array<int, 2> > v(n);
  vector<int> x;
  for (int i = 0; i < n; i++) {
    cin >> v[i][0] >> v[i][1];
    x.push_back(v[i][0]);
    x.push_back(v[i][1]);
  }
  sort(x.begin(), x.end());
  x.resize(unique(x.begin(), x.end()) - x.begin());
  
  vector<int> st[x.size()+1];
  for (int i = 0; i < n; i++) {
    int a = lower_bound(x.begin(), x.end(), v[i][0]) - x.begin() + 1;
    int b = lower_bound(x.begin(), x.end(), v[i][1]) - x.begin() + 1;
    st[b].push_back(a);
  }
  vector<int> dp(x.size()+1, 0);
  int ans = 0;
  for (int i = 1; i <= x.size(); i++) {
    dp[i] = dp[i - 1];
    for (auto j : st[i]) dp[i] = max(dp[i], dp[j] + 1);
    ans = max(ans, dp[i]);
  }
  cout << ans << '\n';
}
