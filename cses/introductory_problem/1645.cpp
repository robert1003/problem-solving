#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  vector<pair<int, int> > q;
  for (int i = 0; i < n; i++) {
    int idx = lower_bound(q.begin(), q.end(), make_pair(v[i], -1)) - q.begin() - 1;
    int ans = (idx < 0 ? 0 : q[idx].second);
    while (q.size() && v[i] <= q.back().first) q.pop_back();
    q.push_back({v[i], i+1});
    cout << ans << " \n"[i == n - 1];
    /*
    for (auto [a, b] : q) {
      cerr << "(" << a << "," << b << ") ";
    }
    cerr << '\n';
    */
  }
}
