#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int m;
vector<array<ll, 2> > prime, prime_tmp;

bool factor(ll x, ll tot) {
  ll tmp = x, sum = 0;
  for(auto [p, n] : prime_tmp) {
    while(x % p == 0) {
      n--; if(n < 0) return false;
      sum += p;
      x /= p;
    }
  }
  return x == 1 && tmp + sum == tot;
}

void init() {
  cin >> m;
  prime.clear();
  for (int i = 0; i < m; i++) {
    ll p, n; cin >> p >> n;
    prime.push_back({p, n});
  }
}
void solve(int kase) {
  ll sum = 0, ans = 0;
  for(auto [p, n] : prime) sum += p * n;
  for(ll i = max(1LL, sum - 500 * 50) ; i < sum ; i++) {
    prime_tmp = prime;
    if(factor(i, sum)) ans = max(ans, i);
  }
  cout << "Case #" << kase << ": " << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t, kase = 1; cin >> t;
  while (t--) {
    init();
    solve(kase++);
  }
}
