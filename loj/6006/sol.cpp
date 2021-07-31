#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic {
    static const int maxN = 10000;
    struct Edge { int v, f, c, re; };
    int n, s, t, level[maxN];
    vector<Edge> E[maxN];

    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
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
                res += tf, nf -= tf, it.f -= tf;
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

int k, n, a[25];
vector<int> b[1005];

void init() {
    cin >> k >> n;
    for (int i = 1; i <= k; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        int m; cin >> m; b[i].resize(m);
        for (int j = 0; j < m; j++) cin >> b[i][j];
    }
}
void solve() {
    int s = 0, t = k + n + 1;
    flow.init(k + n + 2, s, t);
    for (int i = 1; i <= n; i++) {
        flow.add_edge(s, i, 1);
        for (auto j : b[i]) flow.add_edge(i, j + n, 1);
    }
    int sum = 0;
    for (int i = 1; i <= k; i++) flow.add_edge(i + n, t, a[i]), sum += a[i];

    if (flow.flow() != sum) {
        cout << "No Solution!\n";
        return;
    }
    for (int i = 1; i <= k; i++) {
        bool empty = true;
        cout << i << ':';
        for (auto &it : flow.E[i + n]) if (it.c == 0 && it.f > 0 && it.v >= 1 && it.v <= n) {
            cout << ' ' << it.v;
            empty = false;
        }
        if (empty) cout << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
