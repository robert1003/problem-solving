#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ll n; cin >> n;
  vector<ll> p(1<<n);
  for (ll i = 0; i < n; i++) {
    ll x; cin >> x;
    p[1 << i] = x;
  }
  vector<ll> f = p;
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < (1<<n); j++) {
      if (j & (1 << i))
        f[j] += f[j ^ (1 << i)];
    }
  }

  ll tot = f[(1<<n)-1], mndif = LLONG_MAX;
  for (ll i = 0; i < (1<<n); i++) {
    mndif = min(mndif, abs(tot - f[i]*2));
  }
  cout << mndif << '\n';
}
