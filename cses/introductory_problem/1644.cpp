#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, a, b; cin >> n >> a >> b;
  vector<ll> v(n + 1), pre(n + 1, 0);
  for (int i = 0; i < n; i++) cin >> v[i + 1], pre[i + 1] = pre[i] + v[i + 1];
  deque<array<ll, 2> > q;
  q.push_back({0, 0});
  ll ans = -LLONG_MAX;
  for (int i = a; i <= n; i++) {
    ans = max(ans, pre[i] - q.front()[0]);
    while (!q.empty() && q.back()[0] >= pre[i - a + 1]) q.pop_back();
    q.push_back({pre[i - a + 1], i - a + 1});
    while (!q.empty() && q.front()[1] < i - b + 1) q.pop_front();
  }
  cout << ans << '\n';
}
