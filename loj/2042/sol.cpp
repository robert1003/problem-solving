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

const int MXN = 855;
const int INF = (int)1e9;

//n,Dinic::flow must be filled
//result:e[u][v]=u-v mincut;p[u]:u's parent on cut tree
int n,e[MXN][MXN],p[MXN];
void gomory_hu(){
  fill(p, p+n, 0);
  fill(e[0], e[n], INF);
  for(int s = 1 ; s < n ; s++){
    int t = p[s];
    Dinic F; F.init(n,s,t);
    copy(flow.E,flow.E+MXN,F.E);
    int tmp = F.flow();
    for( int i = 0 ; i < s ; i++ )
      e[s][i] = e[i][s] = min(tmp, e[t][i]);
    for( int i = s+1 ; i < n ; i++ )
      if ( p[i] == t && F.level[i]!=-1 ) p[i] = s;
    }
}

int m;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    flow.init(n, 0, 1);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        flow.add_edge(u, v, w);
        flow.add_edge(v, u, w);
    }
    gomory_hu();

    vector<int> v;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) v.push_back(e[i][j]);
    }
    sort(v.begin(), v.end());
    cout << unique(v.begin(), v.end()) - v.begin() << '\n';
}
