#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n; cin >> n;
  int num2 = 0, num5 = 0;
  for (int cur = 2; cur <= n; cur *= 2) {
    num2 += n / cur;
  }
  for (int cur = 5; cur <= n; cur *= 5) {
    num5 += n / cur;
  }
  cout << min(num2, num5) << '\n';
}
