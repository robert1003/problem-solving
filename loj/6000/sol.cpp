#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic {
    static const int maxN = 10000;
    struct Edge { int v, f, re; };
    vector<Edge> E[maxN];
    int n, s, t, level[maxN];

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i = 0; i < n; i++) E[i].clear();
    }
    void add_edge(int u, int v, int f) {
        E[u].push_back({v, f, (int)E[v].size()});
        E[v].push_back({u, 0, (int)E[u].size()-1});
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
                int tf = DFS(it.v, min(it.f, nf));
                res += tf; nf -= tf; it.f -= tf; 
                E[it.v][it.re].f += tf;
                if (nf == 0) return res;
            }
        }
        if (!res) level[u] = -1;
        return res;
    }
    int flow(int res=0) {
        while (BFS()) {
            res += DFS(s, INT_MAX);
        }
        return res;
    }
} flow;

int n, m;
vector<pair<int, int>> v;

void init() {
    cin >> n >> m;
    int a, b;
    while (cin >> a >> b) v.push_back({a, b});
}
void solve() {
    int s = 0, t = n + 1;
    flow.init(n + 2, s, t);
    for (int i = 1; i <= m; i++) flow.add_edge(s, i, 1);
    for (int i = m + 1; i <= n; i++) flow.add_edge(i, t, 1);
    for (auto [a, b] : v) flow.add_edge(a, b, 1);
    cout << flow.flow() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
