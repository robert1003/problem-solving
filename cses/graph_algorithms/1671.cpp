#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, m; cin >> n >> m;
  
  vector<pair<int, int> > G[n + 1];
  for (int i = 0; i < m; i++) {
    int u, v, w; cin >> u >> v >> w;
    G[u].push_back({v, w});
  }
 
  priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
  const ll INF = (ll)1e15;
  vector<ll> d(n + 1, INF), vis(n + 1, 0);
  d[1] = 0;
  pq.push({d[1], 1});
  while (!pq.empty()) {
    auto [_, u] = pq.top(); pq.pop();
    if (vis[u]) continue;
    vis[u] = 1;
 
    for (auto [v, w] : G[u]) {
      if (d[v] > d[u] + w) {
        d[v] = d[u] + w;
        pq.push({d[v], v});
      }
    }
  }
 
  for (int i = 1; i <= n; i++)
    cout << d[i] << " \n"[i == n];
}
