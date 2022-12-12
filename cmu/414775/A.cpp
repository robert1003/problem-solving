#pragma GCC optimize ("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  ll G, A, N; cin >> G >> A >> N;
  vector<ll> gs(G), as(A);
  for (int i = 0; i < G; i++) cin >> gs[i];
  for (int i = 0; i < A; i++) cin >> as[i];
  sort(gs.begin(), gs.end());
  sort(as.begin(), as.end());
 
  auto count = [&](ll w) {
    int j = -1;
    ll cnt = 0;
    for (int i = G-1; i >= 0; i--) {
      while (j+1 < A && gs[i]+as[j+1] <= w) j++;
      cnt += j+1;
    }
    return cnt;
  };
 
  ll l = 2, r = (ll)4e6+10;
  while (l < r) {
    ll mid = l+(r-l)/2;
    if (count(mid) >= N) r = mid;
    else l = mid + 1;
  }
  //cerr << l << ' ' << count(l) << '\n';
 
  ll ans = 0;
  vector<ll> pre(A, 0); pre[0] = as[0];
  for (int i = 1; i < A; i++) pre[i] = pre[i-1]+as[i];
  int j = -1;
  for (int i = G-1; i >= 0; i--) {
    while (j+1 < A && gs[i]+as[j+1] <= l) j++;
    //cerr << i << ' ' << j << '\n';
    if (j >= 0) ans += (ll)gs[i]*(j+1) + pre[j];
  }
  
  ans -= (ll)(count(l) - N) * l;
  cout << ans << '\n';
}
