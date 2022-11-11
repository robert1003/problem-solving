#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
 
  int cities, roads, queries;
  cin >> cities >> roads >> queries;
 
  const ll INF = 1e12;
  vector<vector<ll> > distance(cities, vector<ll>(cities, INF));
  for (int i = 0; i < roads; i++) {
    int src, tgt, weight;
    cin >> src >> tgt >> weight;
    src--; tgt--;
    distance[src][tgt] = min(distance[src][tgt], (ll)weight);
    distance[tgt][src] = min(distance[tgt][src], (ll)weight);
  }
  for (int i = 0; i < cities; i++)
    distance[i][i] = 0;
 
  for (int k = 0; k < cities; k++) {
    for (int i = 0; i < cities; i++) {
      for (int j = 0; j < cities; j++) {
        distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
      }
    }
  }
 
  while (queries--) {
    int query_src, query_tgt;
    cin >> query_src >> query_tgt;
    query_src--; query_tgt--;
    ll ans = distance[query_src][query_tgt];
    if (ans >= INF)
      cout << "-1\n";
    else
      cout << ans << '\n';
  }
}
