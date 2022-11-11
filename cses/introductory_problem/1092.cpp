#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n; cin >> n;
  ll sum = (ll)n * (n + 1) / 2;
  if (sum % 2) cout << "NO\n";
  else {
    cout << "YES\n";
    if (n % 2) {
      cout << n / 2 << '\n';
      cout << n;
      for (int i = 1; i < (n+1)/4; i++)
        cout << ' ' << i << ' ' << n-i;
      cout << '\n';
      cout << (n + 1) / 2 << '\n';
      for (int i = (n+1)/4; i <= n/2; i++)
        cout << i << ' ' << n-i << " \n"[i == n/2];
    }
    else {
      cout << n/2 << '\n';
      for (int i = 1; i <= n/4; i++)
        cout << i << ' ' << n+1-i << " \n"[i == n/4];
      cout << n/2 << '\n';
      for (int i = n/4+1; i <= n/2; i++)
        cout << i << ' ' << n+1-i << " \n"[i == n/2];

    }
  }
}
