#include <bits/stdc++.h>
#define PB push_back
using namespace std;
using ll = long long;

struct Dinic{
  static const ll MXN = 10000;
  struct Edge{ ll v,f,re; };
  ll n,s,t,level[MXN];
  vector<Edge> E[MXN];
  void init(ll _n, ll _s, ll _t){
    n = _n; s = _s; t = _t;
    for (ll i=0; i<n; i++) E[i].clear();
  }
  void add_edge(ll u, ll v, ll f){
    E[u].PB({v,f,(ll)E[v].size()});
    E[v].PB({u,0,(ll)E[u].size()-1});
  }
  bool BFS(){
    for (ll i=0; i<n; i++) level[i] = -1;
    queue<ll> que;
    que.push(s);
    level[s] = 0;
    while (!que.empty()){
      ll u = que.front(); que.pop();
      for (auto &it : E[u]){
        if (it.f > 0 && level[it.v] == -1){
          level[it.v] = level[u]+1;
          que.push(it.v);
        }
      }
    }
    return level[t] != -1;
  }
  ll DFS(ll u, ll nf){
    if (u == t) return nf;
    ll res = 0;
    for (auto &it : E[u]){
      if (it.f > 0 && level[it.v] == level[u]+1){
        ll tf = DFS(it.v, min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0) return res;
      }
    }
    if (!res) level[u] = -1;
    return res;
  }
  ll flow(ll res=0){
    while ( BFS() )
      res += DFS(s,2147483647);
    return res;
  }
}flow;


int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    ll n, m, s, t;
    cin >> n >> m >> s >> t;
    flow.init(n, s - 1, t - 1);
    for (ll i = 0; i < m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        flow.add_edge(u - 1, v - 1, w);
    }
    cout << flow.flow() << '\n';
}
