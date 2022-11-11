#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n, q; cin >> n >> q;
  vector<ll> pre(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> pre[i];
    pre[i] += pre[i - 1];
  }
  while (q--) {
    int l, r; cin >> l >> r;
    cout << pre[r] - pre[l - 1] << '\n';
  }
}
