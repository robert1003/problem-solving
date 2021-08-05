#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct zkwflow{
    static const int N = 10000;
    static const int INF = INT_MAX;
	struct Edge { int v, f, re; ll w; };
	vector<Edge> E[N];
    int n, s, t, ptr[N];
	bool vis[N]; ll d[N];
    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        for (int i = 0; i < n; i++) E[i].clear();
    }
    void add_edge(int u, int v, int f, ll w) {
        E[u].push_back({v, f, (int)E[v].size(), w});
        E[v].push_back({u, 0, (int)E[u].size()-1, -w});
    }
	bool SPFA() {
        fill_n(d, n, LLONG_MAX);
        fill_n(vis, n, false);
		d[s] = 0;
        deque<int> q = { s };
        while (!q.empty()) {
            int u = q.front(); q.pop_front();
            vis[u] = false;
            for (auto &it : E[u]) {
                if (it.f > 0 && d[it.v] > d[u] + it.w) {
                    d[it.v] = d[u] + it.w;
                    if (!vis[it.v]) {
                        vis[it.v] = true;
                        if (!q.empty() && d[it.v] > d[q.front()]) q.push_back(it.v);
                        else q.push_front(it.v);
                    }
                }
            }
        }
		return d[t] != LLONG_MAX;
	}
    int DFS(int u, int nf) {
        if (u == t) return nf;
        vis[u] = true;
        int res = 0;
        for (int &i = ptr[u]; i < (int)E[u].size(); i++) {
            auto &it = E[u][i];
            if (it.f > 0 && d[it.v] == d[u] + it.w && !vis[it.v]) {
                int tf = DFS(it.v, min(nf, it.f));
                res += tf, nf -= tf, it.f -= tf;
                E[it.v][it.re].f += tf;
                if (nf == 0) {
                    vis[u] = false;
                    break;
                }
            }
        }
        return res;
    }
	pair<int, ll> MCMF() {
		int flow = 0; ll cost = 0;
		while (SPFA()) {
			fill_n(ptr, n, 0);
			int dd = DFS(s, INF);
			flow += dd; cost += dd * d[t];
		}
		return { flow, cost };
	}
}flow;

const int INF = (int)1e9;

int n, k;
vector<array<int, 3> > v;
vector<int> x;

inline int convert(int val) {
    return lower_bound(x.begin(), x.end(), val) - x.begin() + 1;
}

void init() {
    cin >> n >> k;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i][0] >> v[i][1];
        if (v[i][0] > v[i][1]) swap(v[i][0], v[i][1]);
        v[i][2] = v[i][1] - v[i][0];
        x.push_back(v[i][0]);
        x.push_back(v[i][1]);
    }
    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());

    for (auto &it : v) {
        it[0] = convert(it[0]);
        it[1] = convert(it[1]);
    }
}
void solve() {
    int s = 0, t = (int)x.size();
    flow.init((int)x.size() + 1, s, t);
    for (int i = 0; i < (int)x.size(); i++) {
        if (i == 0) flow.add_edge(s, i + 1, k, 0);
        else flow.add_edge(i, i + 1, INF, 0);
    }
    for (auto &it : v) {
        flow.add_edge(it[0], it[1], 1, -it[2]);
    }
    cout << -flow.MCMF().second << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
