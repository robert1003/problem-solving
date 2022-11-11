#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> _manacher(string &s) {
  string p = '^' + s + '$';
  int n = p.size();
  vector<int> z(n, 0);
  for (int i = 1, l = 1, r = 1; i < n; i++) {
    if (i <= r)
      z[i] = min(r - i, z[l + (r - i)]);
    while (p[i - z[i]] == p[i + z[i]]) z[i]++;
    if (i + z[i] > r) {
      l = i - z[i], r = i + z[i];
    }
  }

  return vector<int>(z.begin() + 1, z.end() - 1);
}

string manacher(string &s) {
  string p;
  for (auto c : s) {
    p.push_back('#');
    p.push_back(c);
  }
  p.push_back('#');
  vector<int> z = _manacher(p);
  
  int mx = -1, mx_idx = 0;
  for (int i = 0; i < (int)z.size(); i++) {
    if (z[i] > mx)
      mx = z[i], mx_idx = i;
  }

  string ans;
  for (int i = mx_idx - mx + 1; i < mx_idx + mx; i++) {
    if (p[i] != '#') ans.push_back(p[i]);
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  string s; cin >> s;
  cout << manacher(s) << '\n';
}
