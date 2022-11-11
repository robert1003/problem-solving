#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<int> a(n), b(n), x;
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
    x.push_back(a[i]);
    x.push_back(b[i]);
  }
  sort(x.begin(), x.end());
  x.resize(unique(x.begin(), x.end()) - x.begin());
  vector<int> seg[x.size()];
  for (int i = 0; i < n; i++) {
    a[i] = lower_bound(x.begin(), x.end(), a[i]) - x.begin();
    seg[a[i]].push_back(1);
    b[i] = lower_bound(x.begin(), x.end(), b[i]) - x.begin();
    seg[b[i]].push_back(-1);
  }

  int cnt = 0, mx = 0;
  for (int i = 0; i < x.size(); i++) {
    for (auto j : seg[i]) if (j > 0) cnt++;
    mx = max(mx, cnt);
    for (auto j : seg[i]) if (j < 0) cnt--;
  }
  mx = max(mx, cnt);
  cout << mx << '\n';
}
