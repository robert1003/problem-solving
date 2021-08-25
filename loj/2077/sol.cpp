#include <bits/stdc++.h>
#define PB push_back
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
    E[u].PB({v,f,(int)E[v].size()});
    E[v].PB({u,0,(int)E[u].size()-1});
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

int n, m, dis[N][N], t[N][N], ok[N][N], p[N];
vector<array<int, 3> > flight;

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> t[i][j]; dis[i][j] = t[i][j];
        }
    }

    for (int i = 1; i <= m; i++) {
        int x, y, d; cin >> x >> y >> d;
        flight.push_back({x, y, d});
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                t[i][j] = min(t[i][j], t[i][k] + t[k][j] + p[k]);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) continue;
            auto [xi, yi, di] = flight[i];
            auto [xj, yj, dj] = flight[j];
            if (yi == xj && di + dis[xi][yi] + p[yi] <= dj) ok[i][j] = 1;
            if (di + dis[xi][yi] + p[yi] + t[yi][xj] + p[xj] <= dj) ok[i][j] = 1;
        }
    }
}
void solve() {
    int src = 0, snk = m*2+1;
    flow.init(m*2+2, src, snk);
    for (int i = 0; i < m; i++) {
        flow.add_edge(src, (i+1)*2, 1);
        flow.add_edge((i+1)*2-1, snk, 1);
        for (int j = 0; j < m; j++) {
            if (ok[i][j]) {
                flow.add_edge((i+1)*2, (j+1)*2-1, 1);
            }
        }
    }

    cout << m - flow.flow() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
