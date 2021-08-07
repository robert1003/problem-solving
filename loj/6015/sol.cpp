#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic {
    static const int maxN = 100000;
    struct Edge { int v, f, re; };
    int n, s, t, level[maxN];
    vector<Edge> E[maxN];

    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
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

struct DSU {
    static const int maxN = 10000;
    int sz[maxN], pa[maxN], n;

    void init(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) sz[i] = 1, pa[i] = i;
    }
    int find(int x) {
        if (x == pa[x]) return x;
        return pa[x] = find(pa[x]);
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        sz[x] += sz[y];
        pa[y] = x;
        return true;
    }
} dsu;

const int INF = (int)1e9;
const int N = 30;

int n, m, k, h[N];
vector<int> s[N];

inline int ID(int u, int t) {
    return u + (n + 2) * t;
}

void init() {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int r;
        cin >> h[i] >> r;
        s[i].resize(r);
        for (int j = 0; j < r; j++) {
            cin >> s[i][j];
            if (s[i][j] == -1) s[i][j] = n + 1;
        }
    }
}
void solve() {
    // have solution?
    dsu.init(n + 2);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j < (int)s[i].size(); j++) dsu.merge(s[i][j - 1], s[i][j]);
    }
    if (dsu.find(0) != dsu.find(n + 1)) {
        cout << "0\n"; return;
    }

    // iter until flow >= k
    int ss = flow.maxN - 2, tt = flow.maxN - 1, ans = 0, res = 0;
    flow.init(flow.maxN, ss, tt);
    flow.add_edge(ss, 0, INF);
    flow.add_edge(n + 1, tt, INF);
    do {
        flow.add_edge(ss, ID(0, ans + 1), INF);
        for (int i = 1; i <= m; i++) {
            flow.add_edge(ID(i, ans), ID(i, ans + 1), INF);
            flow.add_edge(ID(s[i][ans % s[i].size()], ans), ID(s[i][(ans + 1) % s[i].size()], ans + 1), h[i]);
        }
        flow.add_edge(ID(n + 1, ans + 1), tt, INF);
        res = flow.flow(res);
        ans++;
    } while (res < k);

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    init();
    solve();
}
