#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n, q; cin >> n >> q;
  vector<int> pre(n + 1, 0);
  for (int i = 1; i <= n; i++) cin >> pre[i], pre[i] ^= pre[i - 1];
  while (q--) {
    int a, b; cin >> a >> b;
    cout << (pre[b] ^ pre[a - 1]) << '\n';
  }
}
