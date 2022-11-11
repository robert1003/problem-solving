#pragma GCC optimize ("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, k; cin >> n >> k;
  vector<int> v(n);
  multiset<int> s[2];
  for (int i = 0; i < k; i++) {
    cin >> v[i];
    s[0].insert(v[i]);
  }
  while (s[0].size() > (k+1)/2) {
    s[1].insert(*prev(s[0].end()));
    s[0].erase(prev(s[0].end()));
  }
  for (int i = k; i < n; i++) {
    cout << *prev(s[0].end()) << " ";

    cin >> v[i];
    if (v[i] < *s[1].begin())
      s[0].insert(v[i]);
    else
      s[1].insert(v[i]);

    if (s[1].count(v[i - k])) s[1].erase(s[1].lower_bound(v[i - k]));
    else if (s[0].count(v[i - k])) s[0].erase(s[0].lower_bound(v[i - k]));

    while (s[0].size() > (k+1)/2) {
      s[1].insert(*prev(s[0].end()));
      s[0].erase(prev(s[0].end()));
    }
    while (s[0].size() < (k+1)/2) {
      s[0].insert(*s[1].begin());
      s[1].erase(s[1].begin());
    }
    /*
    cerr << '\n';
    for (auto i : s[0]) cerr << i << ' ';
    cerr << " : ";
    for (auto i : s[1]) cerr << i << ' ';
    cerr << '\n';
    */

  }
  cout << *prev(s[0].end()) << "\n";
}
