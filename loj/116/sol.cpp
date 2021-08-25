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

const int INF = (int)1e9;

vector<int> sum;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m, s, t; cin >> n >> m >> s >> t;
    sum.resize(n + 1);
    flow.init(n + 2, 0, n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, l, r; cin >> u >> v >> l >> r;
        sum[u] -= l; sum[v] += l;
        if (r - l < 0) { cout << "please go home to sleep\n"; exit(0); }
        flow.add_edge(u, v, r - l);
    }
    int tot = 0;
    for (int i = 1; i <= n; i++) {
        if (sum[i] > 0) flow.add_edge(0, i, sum[i]), tot += sum[i];
        else if (sum[i] < 0) flow.add_edge(i, n + 1, -sum[i]);
    }
    flow.add_edge(t, s, INF);
    if (flow.flow() != tot) { cout << "please go home to sleep\n"; exit(0); }
    flow.s = s, flow.t = t;
    cout << flow.flow() << '\n';
}
