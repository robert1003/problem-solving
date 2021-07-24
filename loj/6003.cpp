#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic {
    static const int maxN = 50000;
    struct Edge { int v, f, c, re; };
    int n, s, t, level[maxN];
    vector<Edge> E[maxN];

    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        for (int i = 0; i < n; i++) E[i].clear();
    }
    void add_edge(int u, int v, int f) {
        E[u].push_back({v, f, f, (int)E[v].size()});
        E[v].push_back({u, 0, 0, (int)E[u].size()});
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
        while (BFS()) {
            res += DFS(s, INT_MAX);
        }
        return res;
    }
} flow;

const int maxN = 10000 + 5;

int n, in_deg[maxN];
vector<int> nG[maxN];

void update(int i) {
    for (int j = 1; j < i; j++) if (pow(int(sqrt(i + j)), 2) == i + j) {
        flow.add_edge(j*2-1, i*2, 1);
    }
}
void dfs(int u, vector<int>& path) {
    path.push_back(u);
    for (auto v : nG[u]) dfs(v, path);
}
bool ok(int x) {
    int s = 0, t = x * 2 + 1;
    flow.init(x * 2 + 2, s, t);
    for (int i = 1; i <= x; i++) {
        flow.add_edge(s, i*2-1, 1);
        flow.add_edge(i*2, t, 1);
    }
    for (int i = 1; i <= x; i++) update(i);
    return x - flow.flow() <= n;
}

void init() {
    cin >> n;
}
void solve() {
    int l = n, r = 2000;
    while (l + 1 < r) {
        int mid = (l + r + 1) / 2;
        if (ok(mid)) l = mid;
        else r = mid;
    }

    assert (ok(l));
    for (int i = 1; i <= l * 2; i += 2) {
        for (auto it : flow.E[i]) if (it.c > 0 && it.f == 0) {
            nG[(i + 1) / 2].push_back(it.v / 2);
            in_deg[it.v / 2]++;
        }
    }
    
    cout << l << '\n';
    vector<int> path;
    for (int i = 1; i <= l; i++) if (in_deg[i] == 0) {
        path.clear();
        dfs(i, path);
        for (int j = 0; j < (int)path.size(); j++) cout << path[j] << " \n"[j == (int)path.size() - 1];
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
