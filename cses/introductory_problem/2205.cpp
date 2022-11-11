#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string bin(int x, int n) {
  string s;
  while (x > 0) s.push_back('0'+x%2), x/=2;
  while (s.size() < n) s.push_back('0');
  reverse(s.begin(), s.end());
  return s;
}

int main() {
  int n; cin >> n;
  for (int i = 0; i < (1<<n); i++) {
    cout << bin(i ^ (i >> 1), n) << '\n';
  }
}
