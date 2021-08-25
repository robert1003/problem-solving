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

const int N = 100 + 5;
const int INF = (int)1e9;
const int maxA = 1000;

int n, m, a[N], d[N][N], idx[N][N], cnt;

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) cin >> d[i][j], idx[i][j] = ++cnt;
    }
}
void solve() {
    int s = 0, t = cnt + maxA + 1, psum = 0;
    flow.init(t + 1, s, t);
    set<int> done;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int rev = d[i][j];
            if (i == j) flow.add_edge(idx[i][j], cnt + a[i], INF), rev -= a[i];
            else {
                flow.add_edge(idx[i][j], idx[i + 1][j], INF);
                flow.add_edge(idx[i][j], idx[i][j - 1], INF);
            }

            if (rev > 0) flow.add_edge(s, idx[i][j], rev), psum += rev;
            else if (rev < 0) flow.add_edge(idx[i][j], t, -rev);
        }
    }
    if (m) {
        for (int i = 1; i <= maxA; i++) flow.add_edge(cnt + i, t, i * i);
    }

    cout << psum - flow.flow() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
