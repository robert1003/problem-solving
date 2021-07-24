#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic {
    static const int maxN = 10000;
    struct Edge { int v, f, re; };
    int n, s, t, level[maxN];
    vector<Edge> E[maxN];

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i = 0; i < n; i++) E[i].clear();
    }
    void add_edge(int u, int v, int f) {
        E[u].push_back({v, f, (int)E[v].size()});
        E[v].push_back({u, 0, (int)E[u].size()});
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
                res += tf; it.f -= tf; nf -= tf;
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

const int maxN = 55;
const int inf = (int)1e9;
int m, n, pay[maxN], cost[maxN];
vector<int> equip[maxN];

void init() {
    cin >> m >> n;
    string s; getline(cin, s);
    for (int i = 1; i <= m; i++) {
        getline(cin, s);
        stringstream ss; ss << s;
        ss >> pay[i];
        int eq;
        while (ss >> eq) equip[i].push_back(eq);
    }
    for (int i = 1; i <= n; i++) cin >> cost[i];
}
void solve() {
    int s = 0, t = n + m + 1;
    flow.init(n + m + 2, s, t);
    for (int i = 1; i <= m; i++) {
        flow.add_edge(s, i, pay[i]);
        for (auto j : equip[i]) flow.add_edge(i, j + m, inf);
    }
    for (int i = 1; i <= n; i++) flow.add_edge(i + m, t, cost[i]);

    int rev = -flow.flow();
    for (int i = 1; i <= m; i++) rev += pay[i];

    bool fir = 1;
    for (int i = 1; i <= m; i++) if (flow.level[i] != -1) {
        cout << (fir ? "" : " ") << i;
        fir = 0;
    }
    cout << '\n';

    fir = 1;
    for (int i = 1; i <= n; i++) if (flow.level[i + m] != -1) {
        cout << (fir ? "" : " ") << i;
        fir = 0;
    }
    cout << '\n';

    cout << rev << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
