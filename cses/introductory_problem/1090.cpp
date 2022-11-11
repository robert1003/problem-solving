#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, x; cin >> n >> x;
  vector<int> p(n);
  for (int i = 0; i < n; i++) cin >> p[i];
  sort(p.begin(), p.end());
  int st = 0, ed = n - 1, ans = 0;
  while (st <= ed) {
    if (st == ed) {
      ans++;
      break;
    }
    if (p[st] + p[ed] > x) ans++, ed--;
    else ans++, st++, ed--;
  }
  cout << ans << '\n';
}
