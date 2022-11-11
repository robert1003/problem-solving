#include <bits/stdc++.h>
using namespace std;

int main() {
  int t; cin >> t;
  while (t--) {
    int a, b; cin >> a >> b;
    if ((a + b) % 3 != 0) {
      cout << "NO\n";
      continue;
    }
    int sum = (a + b) / 3;
    int na = a - sum;
    int nb = b - sum;
    if (na < 0 || nb < 0) {
      cout << "NO\n";
      continue;
    }
    cout << "YES\n";
  }
}
