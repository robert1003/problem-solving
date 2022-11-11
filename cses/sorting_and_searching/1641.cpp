#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, x; cin >> n >> x;
  vector<array<int, 2> > a(n);
  for (int i = 0; i < n; i++) cin >> a[i][0], a[i][1] = i;
  sort(a.begin(), a.end());

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int residual = x - a[i][0] - a[j][0];
      auto k = lower_bound(a.begin() + j + 1, a.end(), array<int, 2>{residual, 0});
      if (k == a.end()) continue;
      if ((*k)[0] == residual) {
        cout << a[i][1] + 1 << ' ' << a[j][1] + 1 << ' ' << (*k)[1] + 1 << '\n';
        return 0;
      }
    }
  }

  cout << "IMPOSSIBLE\n";
}
