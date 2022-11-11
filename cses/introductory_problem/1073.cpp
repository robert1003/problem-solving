#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  multiset<int> s;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    auto it = s.upper_bound(x);
    if (it == s.end()) s.insert(x);
    else {
      s.erase(it);
      s.insert(x);
    }
  }
  cout << (int)s.size() << '\n';
}
