#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, m; cin >> n >> m;
  vector<int> v(n), inv(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i], v[i]--;
    inv[v[i]] = i;
  }
  int sum = 1;
  for (int i = 1; i < n; i++) {
    if (inv[i - 1] > inv[i]) sum++;
  }
  while (m--) {
    int a, b; cin >> a >> b;
    a--, b--;
    if (inv[v[a]] > inv[v[b]]) swap(a, b);

    auto test = [&](int x, int y) {
      int cnt = 0;
      if (v[x] - 1 >= 0) {
        if (inv[v[x] - 1] > inv[v[x]] && inv[v[x] - 1] <= y) cnt--;
        if (inv[v[x] - 1] < inv[v[x]] && inv[v[x] - 1] >= y) cnt++;
      }
      if (v[x] + 1 < n) {
        if (inv[v[x] + 1] > inv[v[x]] && inv[v[x] + 1] <= y) cnt++;
        if (inv[v[x] + 1] < inv[v[x]] && inv[v[x] + 1] >= y) cnt--;
      }
      return cnt;
    };

    int adjust = (abs(v[a] - v[b]) == 1 ? (v[a] < v[b] ? -1 : 1) : 0);
    sum += test(a, b) + test(b, a) + adjust;
    cout << sum << '\n';
    swap(inv[v[a]], inv[v[b]]);
    swap(v[a], v[b]);
    //for (int i = 0; i < n; i++) cerr << v[i] << " \n"[i == n - 1];
    //for (int i = 0; i < n; i++) cerr << inv[i] << " \n"[i == n - 1];
  }
}
