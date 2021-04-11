#include <bits/stdc++.h>
using namespace std;

const int N = 100 + 5;

int n, a[N];

void init() {
  cin >> n;
  for(int i = 1 ; i <= n ; ++i) cin >> a[i];
}
void solve(int kase) {
  int cost = 0;
  for(int i = 1 ; i < n ; ++i) {
    int k = i, mn = a[k];
    for(int j = i + 1 ; j <= n ; ++j) if(a[j] < mn) {
      mn = a[j]; k = j;
    }
    cost += k - i + 1;
    reverse(a + i, a + k + 1);
  }
  cout << "Case #" << kase << ": " << cost << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t, kase = 1; cin >> t;
  while(t--) {
    init();
    solve(kase++);
  }
}
