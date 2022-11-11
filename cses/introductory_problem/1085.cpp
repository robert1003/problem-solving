#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, k; cin >> n >> k;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];

  auto ok = [&](ll x) {
    int cnt = 1;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      if (sum + v[i] > x) {
        cnt++;
        sum = v[i];
        if (sum > x) return false;
      }
      else sum += v[i];
    }
    return cnt <= k;
  };

  ll l = 0, r = 2e15;
  while (l < r) {
    ll mid = l + (r - l) / 2;
    if (ok(mid)) r = mid;
    else l = mid + 1;
  }
  cout << l << '\n';
}
