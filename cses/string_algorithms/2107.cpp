#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> z_algo(string &s) {
  int n = s.size();
  vector<int> z(n, 0);
  for (int i = 1, l = 0, r = -1; i < n; i++) {
    if (i <= r)
      z[i] = min(z[i - l], r - i + 1);
    while (z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }

  return z;
}

vector<int> kmp(string &s) {
  int n = s.size();
  vector<int> f(n, 0);
  for (int i = 1; i < n; i++) {
    int j = f[i - 1];
    while (j && s[j] != s[i]) j = f[j - 1];
    if (s[j] == s[i]) j++;
    f[i] = j;
  }

  return f;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  string s; cin >> s;
  vector<int> z = z_algo(s);
  vector<int> f = kmp(s);
  int n = s.size();
  for (int i = 0; i < n; i++) cout << z[i] << " \n"[i == n - 1];
  for (int i = 0; i < n; i++) cout << f[i] << " \n"[i == n - 1];
}
