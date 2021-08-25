#include <bits/stdc++.h>
#define PB push_back
using namespace std;
using ll = long long;

#define SZ(c) ((int)(c).size())
struct Maxflow {
  static const int MAXV = 50010;
  static const int INF  = 1000000;
  struct Edge {
    int v, c, r;
    Edge(int _v, int _c, int _r):
      v(_v), c(_c), r(_r) {}
  };
  int s, t;
  vector<Edge> G[MAXV];
  int iter[MAXV], d[MAXV], gap[MAXV], tot;
  void init(int n, int _s, int _t) {
    tot = n, s = _s, t = _t;
    for(int i = 0; i <= tot; i++) {
      G[i].clear();
      iter[i] = d[i] = gap[i] = 0;
    }
  }
  void add_edge(int u, int v, int c) {
    G[u].push_back(Edge(v, c, SZ(G[v]) ));
    G[v].push_back(Edge(u, 0, SZ(G[u]) - 1));
  }
  int DFS(int p, int flow) {
    if(p == t) return flow;
    for(int &i = iter[p]; i < SZ(G[p]); i++) {
      Edge &e = G[p][i];
      if(e.c > 0 && d[p] == d[e.v]+1) {
        int f = DFS(e.v, min(flow, e.c));
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
    for(res = 0; d[s] < tot; res += DFS(s, INF));
    return res;
  }
} flow;

const int N = 250 + 5;

int n, m, k, a[N][N];

bool ok(int x) {
    int s = 0, t = n + m + 1;
    flow.init(n + m + 2, s, t);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] <= x) flow.add_edge(i + 1, j + 1 + n, 1);
        }
    }
    for (int i = 0; i < n; i++) flow.add_edge(s, i + 1, 1);
    for (int j = 0; j < m; j++) flow.add_edge(j + 1 + n, t, 1);

    return flow.flow() >= n - k + 1;
}

void init() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
}
void solve() {
    int l = 1, r = (int)1e9;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (ok(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
