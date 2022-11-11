#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, x; cin >> n >> x;
  vector<pair<int, int> > a(n);
  for (int i = 0; i < n; i++) {
    int b; cin >> b;
    a[i] = {b, i + 1};
  }
  sort(a.begin(), a.end());
  int r = n - 1;
  array<int, 2> ans = {-1, -1};
  for (int l = 0; l < n; l++) {
    while (r > l && a[l].first + a[r].first > x) r--;
    if (l != r && a[l].first + a[r].first == x) {
      ans[0] = a[l].second;
      ans[1] = a[r].second;
      break;
    }
  }
  if (ans[0] == -1) cout << "IMPOSSIBLE\n";
  else cout << ans[0] << ' ' << ans[1] << '\n';
}
