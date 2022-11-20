#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll M = (ll)1e9+7;

ll powmod(ll a, ll b) {
  if (!b) return 1;
  ll ans = powmod(a, b>>1);
  ans = ans * ans % M;
  if (b&1) ans = ans * a % M;
  return ans;
}

vector<ll> fac, ifac;

void build(int n) {
  fac.resize(n+1), ifac.resize(n+1);
  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % M;
  ifac[n] = powmod(fac[n], M-2);
  for (int i = n-1; i >= 0; i--) ifac[i] = ifac[i+1] * (i+1) % M;
}
ll C(int n, int m) {
  if (n < m) return 0;
  return fac[n]*ifac[m] % M * ifac[n-m] % M;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  build(200000);
  int h, w, n; cin >> h >> w >> n;
  vector<pair<int, int>> pts(n+1);
  for (int i = 0; i < n; i++) cin >> pts[i].first >> pts[i].second;
  pts[n] = {h, w};
  sort(pts.begin(), pts.end());
  vector<ll> dp(n+1);
  for (int i = 0; i < n+1; i++) {
    auto [x, y] = pts[i];
    dp[i] = C(x+y-2, x-1);
  }
  for (int i = 1; i < n+1; i++) {
    for (int j = 0; j < i; j++) {
      auto [x, y] = pts[i];
      auto [x2, y2] = pts[j];
      dp[i] = (dp[i] - dp[j]*C(x-x2+y-y2, x-x2)%M + M) % M;
    }
  }

  cout << dp[n] << '\n';
}
