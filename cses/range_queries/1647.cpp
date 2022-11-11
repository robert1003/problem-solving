#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  int lgN = __lg(n) + 1;
  vector<vector<int> > v(n, vector<int>(lgN, 0));
  for (int i = 0; i < n; i++) cin >> v[i][0];
  for (int j = 1; j < lgN; j++) {
    for (int i = 0; i + (1 << j) <= n; i++) {
      v[i][j] = min(v[i][j - 1], v[i + (1 << (j - 1))][j - 1]);
    }
  }

  while (q--) {
    int a, b; cin >> a >> b;
    a--, b--;
    int k = __lg(b - a + 1);
    cout << min(v[a][k], v[b - (1 << k) + 1][k]) << '\n';
  }
}
