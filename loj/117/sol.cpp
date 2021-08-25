#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
#define PB push_back
using namespace std;
using ll = long long;

#define SZ(c) ((int)(c).size())
struct Maxflow {
  static const int MAXV = 50010;
  static const int INF  = INT_MAX;
  struct Edge {
    int v, c, r;
    Edge(int _v, int _c, int _r):
      v(_v), c(_c), r(_r) {}
  };
  int s, t;
  vector<Edge> G[MAXV];
  int iter[MAXV], d[MAXV], gap[MAXV], tot;
  void init(int x, int _s, int _t) {
    tot = x+2;
    s = _s, t = _t;
    for(int i = 0; i <= tot; i++) {
      G[i].clear();
      iter[i] = d[i] = gap[i] = 0;
    }
  }
  void add_edge(int u, int v, int c) {
    G[u].push_back(Edge(v, c, SZ(G[v]) ));
    G[v].push_back(Edge(u, 0, SZ(G[u]) - 1));
  }
  int dfs(int p, int flow) {
    if(p == t) return flow;
    for(int &i = iter[p]; i < SZ(G[p]); i++) {
      Edge &e = G[p][i];
      if(e.c > 0 && d[p] == d[e.v]+1) {
        int f = dfs(e.v, min(flow, e.c));
        if(f) {
          e.c -= f;
          G[e.v][e.r].c += f;
          return f;
        }
      }
    }
    if( (--gap[d[p]]) == 0) d[s] = tot;
    else {
      d[p]++;
      iter[p] = 0;
      ++gap[d[p]];
    }
    return 0;
  }
  int flow() {
    int res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;


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
    flow.s = t, flow.t = s;
    cout << INF - flow.flow() << '\n';
}
