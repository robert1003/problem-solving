#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#pragma GCC target ("sse3,avx,avx2,mmx")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = (ll)1e9+7;

vector<ll> fac, rfac;

ll powmod(ll a, ll b) {
  if (!b) return 1;
  ll ans = powmod(a, b >> 1);
  ans = ans * ans % mod;
  if (b&1) ans = ans * a % mod;
  return ans;
}
void build(int k) {
  fac.resize(k+1), rfac.resize(k+1);
  fac[0] = 1;
  for (int i = 1; i <= k; i++) fac[i] = fac[i-1] * i % mod;
  rfac[k] = powmod(fac[k], mod-2);
  for (int i = k-1; i >= 0; i--) rfac[i] = rfac[i+1] * (i+1) % mod;
}
inline ll C(ll n, ll m) {
  if (n < m) return 0;
  return fac[n] * rfac[m] % mod * rfac[n-m] % mod;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, m, K, s; cin >> n >> m >> K >> s;
  if (K == 0) {
    cout << s << '\n';
    return 0;
  }
  vector<pair<int, int>> pts;
  for (int i = 0; i < K; i++) {
    int x, y; cin >> x >> y;
    pts.push_back({x, y});
  }
  sort(pts.begin(), pts.end());
  int aug = 0;
  if (pts.front() != make_pair(1, 1))
    pts.insert(pts.begin(), {1, 1}), aug++;
  if (pts.back() != make_pair(n, m))
    pts.push_back({n, m}), aug++;

  build(n+m);
  K += aug;
  vector<vector<ll>> dp(K+1, vector<ll>(K+1, 0));
  
  dp[1][1] = 1; // (1,1)
  int mxK = __lg(s)+aug;
  for (int j = 2; j <= min(K, mxK); j++) {
    // p_k -> p_i
    for (int i = 1; i <= K; i++) {
      auto [xi, yi] = pts[i-1];
      for (int k = 1; k < i; k++) {
        auto [xk, yk] = pts[k-1];
        dp[i][j] = (dp[i][j] + dp[k][j-1]*C(xi-xk+yi-yk, xi-xk) % mod) % mod;
      }
    }

    // p_k -> p_? -> p_i
    for (int i = 1; i <= K; i++) {
      auto [xi, yi] = pts[i-1];
      for (int k = 1; k < i; k++) {
        auto [xk, yk] = pts[k-1];
        dp[i][j] = (dp[i][j] - dp[k][j]*C(xi-xk+yi-yk, xi-xk) % mod + mod) % mod;
      }
    }
  }
  /*
  for (int j = 1; j <= K; j++) {
    for (int i = 1; i <= K; i++) {
      cerr << dp[i][j] << ' ';
    }
    cerr << '\n';
  }
  cerr << '\n';
  */
  ll ans = 0, cur = s, tot = C(n-1+m-1, n-1), sum = 0;
  for (int i = 0; i < 2-aug; i++) {
    cur = (cur+1) / 2;
  }
  for (int i = 2; i <= min(K, mxK); i++) {
    //cerr << i << ' ' << cur << ' ' << dp[K][i] << '\n';
    ans = (ans + dp[K][i] * cur % mod) % mod;
    cur = (cur+1) / 2;
    sum = (sum + dp[K][i]) % mod;
  }
  ans = (ans + tot - sum + mod) % mod;

  ans = ans * powmod(tot, mod-2) % mod;
  cout << ans << '\n';
}
