#include <bits/stdc++.h>
using namespace std;

void solve(int n, int s, int t, int e) {
  if (n == 0) return;
  solve(n - 1, s, e, t);
  cout << s << ' ' << e << '\n';
  solve(n - 1, t, s, e);
}

int main() {
  int n; cin >> n;
  cout << (1<<n)-1 << '\n';
  solve(n, 1, 2, 3);
}
