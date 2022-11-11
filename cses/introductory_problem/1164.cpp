#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  set<array<int, 3> > customer;
  for (int i = 0; i < n; i++) {
    int l, r; cin >> l >> r;
    customer.insert({l, r, i});
  }

  vector<int> ans(n);
  int gid = 1;
  for (gid ; !customer.empty(); gid++) {
    array<int, 3> now = {0, 0, 0};
    while (1) {
      auto it = customer.upper_bound(now);
      if (it == customer.end()) break;
      now = *it;
      ans[now[2]] = gid;
      now[0] = now[1];
      now[1] = INT_MAX;
      customer.erase(it);
    }
  }

  cout << gid - 1 << '\n';
  for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n - 1];
}
