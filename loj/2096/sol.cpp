#include <bits/stdc++.h>
#define int long long
using namespace std;
using ll = long long;

struct Dinic{
  static const int MXN = 10000;
  struct Edge{ int v,f,re; };
  int n,s,t,level[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f){
    E[u].push_back({v,f,(int)E[v].size()});
    E[v].push_back({u,0,(int)E[u].size()-1});
  }
  bool BFS(){
    for (int i=0; i<n; i++) level[i] = -1;
    queue<int> que;
    que.push(s);
    level[s] = 0;
    while (!que.empty()){
      int u = que.front(); que.pop();
      for (auto &it : E[u]){
        if (it.f > 0 && level[it.v] == -1){
          level[it.v] = level[u]+1;
          que.push(it.v);
        }
      }
    }
    return level[t] != -1;
  }
  int DFS(int u, int nf){
    if (u == t) return nf;
    int res = 0;
    for (auto &it : E[u]){
      if (it.f > 0 && level[it.v] == level[u]+1){
        int tf = DFS(it.v, min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0) return res;
      }
    }
    if (!res) level[u] = -1;
    return res;
  }
  int flow(int res=0){
    while ( BFS() )
      res += DFS(s,2147483647);
    return res;
  }
}flow;

const int N = 500 + 5;
const ll INF = (ll)1e12;

int n, m, c[N], pa[N], vis[N];
ll dis[N];
vector<pair<int, int> > G[N];

void dijkstra(int s) {
    fill(dis + 1, dis + 1 + n, INF);
    dis[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    pq.push({dis[s], s});
    while (!pq.empty()) {
        auto res = pq.top(); pq.pop();
        if (vis[res.second]) continue;
        auto [_, u] = res;
        vis[u] = 1;

        for (auto [v, w] : G[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pa[v] = u;
                pq.push({dis[v], v});
            }
        }
    }
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    for (int i = 1; i <= n; i++) cin >> c[i];
    dijkstra(n);
}
void solve() {
    int s = 0, t = n*2+1;
    flow.init(n*2+2, s, t);
    for (int i = 1; i <= n; i++) {
        if (i > 1 && i < n) flow.add_edge(i*2-1, i*2, c[i]);
        else flow.add_edge(i*2-1, i*2, INF);

        for (auto [v, w] : G[i]) {
            if (dis[v] == dis[i] + w) flow.add_edge(v*2, i*2-1, INF);
        }
    }
    flow.add_edge(s, 1, INF);
    flow.add_edge(n*2, t, INF);

    cout << flow.flow() << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
