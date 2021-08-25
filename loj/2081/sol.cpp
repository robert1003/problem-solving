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

const int maxA = (int)2e5 + 5;
const int N = 3005;

vector<bool> isp;
vector<int> v;
int n, a[N];

void build() {
    isp.resize(maxA);
    fill(isp.begin(), isp.end(), 1);
    isp[0] = isp[1] = 0;
    for (int i = 2; i * i < maxA; i++) {
        for (int j = i * i; j < maxA; j += i) isp[j] = 0;
    }
}
void init() {
    cin >> n;
    bool have_one = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], have_one |= (a[i] == 1);
    if (have_one) v.push_back(1);
    for (int i = 1; i <= n; i++) if (a[i] != 1) v.push_back(a[i]);
    n = (int)v.size();
}
void solve() {
    int s = 0, t = n + 1;
    flow.init(n + 2, s, t);
    for (int i = 0; i < n; i++) {
        if (v[i] % 2 == 0) flow.add_edge(s, i + 1, 1);
        else flow.add_edge(i + 1, t, 1);
        for (int j = i + 1; j < n; j++) {
            if (i == j) continue;
            if (isp[v[i] + v[j]]) {
                if (v[i] % 2 == 0) flow.add_edge(i + 1, j + 1, 1);
                else flow.add_edge(j + 1, i + 1, 1);
            }
        }
    }
    cout << n - flow.flow() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    build();
    init();
    solve();
}
