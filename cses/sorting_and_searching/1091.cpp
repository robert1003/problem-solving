#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n, m; cin >> n >> m;
  vector<int> h(n), t(m);
  for (int i = 0; i < n; i++) cin >> h[i];
  for (int i = 0; i < m; i++) cin >> t[i];
  sort(h.begin(), h.end());
  multiset<int> s(h.begin(), h.end());
  for (auto x : t) {
    if (s.empty()) {
      cout << "-1\n";
      continue;
    }
    auto it = s.upper_bound(x);
    if (it == s.begin()) {
      if (*it > x) {
        cout << "-1\n";
      }
      else {
        cout << *it << '\n';
        s.erase(it);
      }
    }
    else {
      it = prev(it);
      cout << *it << '\n';
      s.erase(it);
    }
  }
}
