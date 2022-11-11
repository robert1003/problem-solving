#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n; cin >> n;
  vector<int> v(n), inv(n);
  for (int i = 0; i < n; i++) cin >> v[i], v[i]--, inv[v[i]] = i;
  int ans = 1;
  for (int i = 1; i < n; i++) {
    if (inv[i - 1] > inv[i]) ans++;
  }
  cout << ans << '\n';
}
