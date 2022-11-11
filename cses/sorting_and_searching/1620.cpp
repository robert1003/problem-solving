#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, t; cin >> n >> t;
  vector<int> k(n);
  for (int i = 0; i < n; i++) cin >> k[i];

  auto count = [&](ll x) {
    ll cnt = 0;
    for (int i = 0; i < n; i++) cnt = min((ll)t, cnt + x / k[i]);
    return cnt;
  };

  ll l = 0, r = (ll)1e18;
  while (l < r) {
    ll mid = l + (r - l) / 2;
    if (count(mid) >= t) r = mid;
    else l = mid + 1;
  }

  cout << l << '\n';
}
