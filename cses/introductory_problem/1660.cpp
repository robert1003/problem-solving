#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, x;
vector<ll> v;
ll ans = 0;

void solve(int l, int r) {
  if (l == r) {
    if (v[l] == x) ans++;
    return;
  }
  int mid = l + (r - l) / 2;
  solve(l, mid);
  solve(mid + 1, r);

  vector<ll> sum;
  for (ll i = mid+1, cur = 0; i <= r; i++) {
    cur += v[i];
    sum.push_back(cur);
  }
  sort(sum.begin(), sum.end());
  for (ll i = mid, cur = 0; i >= l; i--) {
    cur += v[i];
    auto [it_l, it_r] = equal_range(sum.begin(), sum.end(), x - cur);
    ans += it_r - it_l;
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> x;
  v.resize(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  solve(0, n-1);
  cout << ans << '\n';
}
