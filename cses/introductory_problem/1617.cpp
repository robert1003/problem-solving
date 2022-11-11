#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = (int)1e9+7;

ll powmod(ll a, ll b) {
  if (!b) return 1;
  ll ans = powmod(a, b >> 1);
  ans = ans * ans % mod;
  if (b & 1) ans = ans * a % mod;
  return ans;
}

int main() {
  int n; cin >> n;
  cout << powmod(2, n) << '\n';
}
