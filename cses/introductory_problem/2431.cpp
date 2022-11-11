#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  
  auto solve = [&](ll x) {
    ll len = 1, num = 9, tot = 0;
    while (x > num*len) x -= num * len, tot += num, num *= 10, len++;
    tot += x / len;
    x %= len; 
    if (x == 0) return tot % 10;
    x = len - x;
    tot++;
    while (x > 0) x--, tot /= 10;
    return tot % 10;
  };

  int q;
  cin >> q;
  while (q--) {
    ll k; cin >> k;
    cout << solve(k) << '\n';
  }
}
