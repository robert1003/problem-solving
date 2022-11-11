#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> z_algo(string& s) {
  vector<int> z(s.size(), 0);
  for (int i = 1, j = 0; i < (int)s.size(); i++) {
    if (i < j+z[j]) z[i] = min(z[i-j], j+z[j]-i);
    while (z[i] < (int)s.size() && s[z[i]] == s[i+z[i]]) z[i]++;
    if (i+z[i] > j+z[j]) j = i;
  }
  return z;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  string s, t; cin >> s >> t;
  string p = t + "@" + s;
  cerr << p.size() << '\n';
  auto z_value = z_algo(p);
  cerr << '\n';
  int ans = 0;
  for (int i = (int)t.size()+1, j = 0; j < (int)s.size(); i++, j++) {
    if (z_value[i] >= (int)t.size()) ans++;
  }
  cout << ans << '\n';
}
