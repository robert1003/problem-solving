#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n; cin >> n;
  vector<int> v(n), closest(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  map<int, int> rightest;
  for (int i = 0; i < n; i++) {
    if (rightest.count(v[i]))
      closest[i] = rightest[v[i]];
    else
      closest[i] = -1;
    rightest[v[i]] = i;
  }

  int ans = 1, l = 0;
  for (int r = 1; r < n; r++) {
    if (closest[r] >= l) l = closest[r] + 1;
    ans = max(ans, r - l + 1);
  }
  cout << ans << '\n';
}
