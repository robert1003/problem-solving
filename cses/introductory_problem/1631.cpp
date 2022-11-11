#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  sort(v.begin(), v.end());

  if (n == 1) {
    cout << v[0] * 2 << '\n';
    return 0;
  }

  ll tot = 0;
  for (int i = 0; i < n; i++) tot += v[i];
  ll cut = 0, cursum = 0;
  for (int i = 0; i < n; i++) {
    cursum += v[i];
    if (cursum > tot - cursum) {
      cursum -= v[i];
      cut = i - 1;
      break;
    }
  }
  
  if (cut == n - 2) {
    cout << v.back() * 2 << '\n';
  }
  else {
    cout << tot << '\n';
  }
}
