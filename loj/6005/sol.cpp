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
        cerr << u << ' ' << v << ' ' << f << '\n';
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

const int N = 500 + 5;

int n, a[N], dp[N];

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}
void solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) if (a[j] <= a[i]) {
            dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';

    int s = 0, t = n * 2 + 1;
    flow.init(n * 2 + 2, s, t);
    for (int i = 1; i <= n; i++) {
        if (dp[i] == 1) flow.add_edge(s, i * 2 - 1, 1);
        if (dp[i] == ans) flow.add_edge(i * 2, t, 1);
        flow.add_edge(i * 2 - 1, i * 2, 1);
        for (int j = 1; j < i; j++) if (a[j] <= a[i] && dp[i] == dp[j] + 1) {
            flow.add_edge(j * 2, i * 2 - 1, 1);
        }
    }
    int res = flow.flow();
    cout << res << '\n';
cerr << '\n';
    
    int inf = 100000;
    flow.add_edge(s, 1, inf);
    flow.add_edge(1, 2, inf);
    if (dp[n] == ans && dp[n] != 1) {
        flow.add_edge(n*2-1, n*2, inf);
        flow.add_edge(n*2, t, inf);
    }

    cout << flow.flow(res) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
