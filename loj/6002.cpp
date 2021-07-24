#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic {
    static const int maxN = 10000;
    struct Edge { int v, f, c, re; };
    int n, s, t, level[maxN];
    vector<Edge> E[maxN];

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i = 0; i < n; i++) E[i].clear();
    }
    void add_edge(int u, int v, int f) {
        E[u].push_back({v, f, f, (int)E[v].size()});
        E[v].push_back({u, 0, 0, (int)E[u].size()-1});
    }
    bool BFS() {
        fill(level, level + n, -1);
        level[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &it : E[u]) {
                if (it.f > 0 && level[it.v] == -1) {
                    level[it.v] = level[u] + 1;
                    q.push(it.v);
                }
            }
        }
        return level[t] != -1;
    }
    int DFS(int u, int nf) {
        if (u == t) return nf;
        int res = 0;
        for (auto &it : E[u]) {
            if (it.f > 0 && level[it.v] == level[u] + 1) {
                int tf = DFS(it.v, min(nf, it.f));
                res += tf; nf -= tf; it.f -= tf;
                E[it.v][it.re].f += tf;
                if (nf == 0) return res;
            }
        }
        if (res == 0) level[u] = -1;
        return res;
    }
    int flow(int res=0) {
        while (BFS())
            res += DFS(s, INT_MAX);
        return res;
    }
} flow;

const int N = 205;

int n, m, vis[N], in_deg[N];
vector<int> G[N], nG[N];

void dfs(int u, vector<int>& path) {
    path.push_back(u); vis[u] = 1;
    for (auto v : nG[u]) dfs(v, path);
    return;
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        G[a].push_back(b);
    }
}
void solve() {
    int s = 0, t = n * 2 + 1;
    flow.init(n * 2 + 2, s, t);
    for (int i = 1; i <= n; i++) {
        flow.add_edge(s, i*2-1, 1);
        flow.add_edge(i*2, t, 1);
    }
    for (int i = 1; i <= n; i++) {
        for (auto j : G[i]) {
            flow.add_edge(i*2-1, j*2, 1);
        }
    }
    int cnt = n - flow.flow();
    for (int i = 1; i <= n * 2; i++) if (i % 2 == 1) {
        for (auto &it : flow.E[i]) if (it.c > 0 && it.f == 0) {
            nG[(i + 1) / 2].push_back(it.v / 2);
            in_deg[it.v / 2]++;
        }
    }

    vector<int> path;
    for (int i = 1; i <= n; i++) if (!in_deg[i]) {
        path.clear();
        dfs(i, path);
        for (int j = 0; j < (int)path.size(); j++) cout << path[j] << " \n"[j == (int)path.size() - 1];
    }
    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
