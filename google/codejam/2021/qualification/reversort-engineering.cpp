#include <bits/stdc++.h>
using namespace std;

const int N = 100 + 5;

int n, c, a[N], op[N];

void init() {
  cin >> n >> c;
}
void solve(int kase) {
  fill(op + 1, op + n, 1); c -= n - 1;
  for(int i = 1 ; i < n && c > 0 ; ++i) {
    int len = min(n - i, c);
    op[i] = i + len;
    c -= len;
  }
  //for(int i = 1 ; i <= n ; ++i) cerr << op[i] << " \n"[i == n];

  cout << "Case #" << kase << ": ";
  if(c == 0) {
    iota(a + 1, a + n + 1, 1); // fill a1 ~ an with 1 ~ n
    for(int i = n - 1 ; i >= 1 ; --i) {
      reverse(a + i, a + op[i] + 1);
    }
    for(int i = 1 ; i <= n ; ++i) cout << a[i] << " \n"[i == n];
  }
  else cout << "IMPOSSIBLE\n";
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t, kase = 1; cin >> t;
  while(t--) {
    init();
    solve(kase++);
  }
}
