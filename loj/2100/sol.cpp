#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic{
  static const int MXN = 251000;
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
const int INF = (int)1e9;

int n, b[N][N], c[N];

void init() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> b[i][j];
    }
    for (int i = 0; i < n; i++) cin >> c[i];
}
void solve() {
    int s = 0, t = n*n+n+1, sum = 0;
    flow.init(n*n+n+2, s, t);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += b[i][j];
            int idx = n*i+j+1;
            flow.add_edge(s, idx, b[i][j]);
            flow.add_edge(idx, n*n+i+1, INF);
            flow.add_edge(idx, n*n+j+1, INF);
        }
        flow.add_edge(n*n+i+1, t, c[i]);
    }

    cout << sum - flow.flow() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
