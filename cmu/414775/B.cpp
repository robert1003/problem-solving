#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<int> G[n];
  vector<int> deg(n, 0), done(n, 0);
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (x != -1) {
      x--;
      G[x].push_back(i);
      deg[i]++;
    }
  }
 
  int len = 0;
  while (1) {
    vector<int> todo;
    for (int i = 0; i < n; i++) {
      if (deg[i] == 0 && !done[i]) {
        todo.push_back(i);
      }
    }
    for (auto u : todo) {
      done[u] = 1;
      for (auto v : G[u]) deg[v]--;
    }
    if (todo.empty()) break;
    len++;
  }
  cout << len << '\n';
}
