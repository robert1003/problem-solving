#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic {
    static const int maxN = 10000;
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
                int tf = DFS(it.v, min(it.f, nf));
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

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const int INF = INT_MAX;

int n, m, a[105][105];

inline int getIdx(int i, int j) {
    return (i - 1) * m + j;
}

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cin >> a[i][j];
    }
}
void solve() {
    int s = 0, t = n * m + 1, sum = 0;
    flow.init(n * m + 2, s, t);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            sum += a[i][j];
            if ((i + j) % 2 == 0) flow.add_edge(s, getIdx(i, j), a[i][j]);
            else flow.add_edge(getIdx(i, j), t, a[i][j]);

            if ((i + j) % 2 == 0) {
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (x >= 1 && x <= n && y >= 1 && y <= m) {
                        flow.add_edge(getIdx(i, j), getIdx(x, y), INF);
                    }
                }
            }
        }
    }
    cout << sum - flow.flow() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
