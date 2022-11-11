#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, m, k; cin >> n >> m >> k;
  vector<int> a(n), b(m);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < m; i++) cin >> b[i];
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  int ans = 0;
  for (int i = 0, j = 0; i < n && j < m; i++) {
    while (j < m && a[i] - b[j] > k) j++;
    if (j == m) break;
    if (abs(a[i] - b[j]) <= k) ans++, j++;
  }
  cout << ans << '\n';
}
