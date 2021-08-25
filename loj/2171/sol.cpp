#include <bits/stdc++.h>
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

int n, m, r, t, k;
vector<pair<int, int> > v;

void init() {
    cin >> n >> m >> r >> t >> k;
    for (int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        v.push_back({a, b});
    }
}
void solve() {
    int src = 0, snk = n+m+1;
    flow.init(n+m+2, src, snk);
    for (int i = 1; i <= m; i++) flow.add_edge(i + n, snk, 1);
    for (auto [a, b] : v) {
        flow.add_edge(a, b + n, 1);
    }

    int cnt = 0, spent = 0;
    for (int i = 0; i < t / r; i++) {
        for (int j = 1; j <= n; j++) flow.add_edge(src, j, 1);
        int res = flow.flow();
        if (res == 0) break;
        cnt += res;
        spent += (i + 1) * r * res;
    }

    cout << cnt << ' ' << spent << '\n';
    for (int i = 1; i <= n; i++) {
        int clk = 0;
        for (auto [v, f, re] : flow.E[i]) {
            if (v > n && v <= n + m && f == 0) cout << i << ' ' << v - n << ' ' << clk << '\n', clk += r;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
