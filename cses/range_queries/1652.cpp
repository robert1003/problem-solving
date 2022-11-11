#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<vector<int> > v(n + 1, vector<int>(n + 1, 0));
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    for (int j = 0; j < n; j++) {
      v[i + 1][j + 1] = v[i][j + 1] + v[i + 1][j] - v[i][j] + (s[j] == '*');
    }
  }
  while (q--) {
    int y[2], x[2];
    cin >> y[0] >> x[0] >> y[1] >> x[1];
    cout << v[y[1]][x[1]] - v[y[0] - 1][x[1]] - v[y[1]][x[0] - 1] + v[y[0] - 1][x[0] - 1] << '\n';
  }
}
