#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct zkwflow {
	static const int maxN = 100000 + 5;
	struct Edge { int v, f, re; ll w; };
	int n, s, t, ptr[maxN];
	bool vis[maxN]; ll dis[maxN];
	vector<Edge> E[maxN];

	void init(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		for (int i = 0; i < n; i++) E[i].clear();
	}
	void add_edge(int u, int v, int f, ll w) {
		E[u].push_back({v, f, (int)E[v].size(), w});
		E[v].push_back({u, 0, (int)E[u].size()-1, -w});
	}
	bool SPFA() {
		fill_n(dis, n, LLONG_MAX);
		fill_n(vis, n, false);

		dis[s] = 0;
		queue<int> q; q.push(s);

		while (!q.empty()) {
			int u = q.front(); q.pop();
			vis[u] = false;

			for (auto &it : E[u]) {
				if (it.f > 0 && dis[it.v] > dis[u] + it.w) {
					dis[it.v] = dis[u] + it.w;
					if (!vis[it.v]) {
						vis[it.v] = true;
						q.push(it.v);
					}
				}
			}
		}

		return dis[t] != LLONG_MAX;
	}
	int DFS(int u, int nf) {
		if (u == t) return nf;
		int res = 0; vis[u] = true;
		for (int &i = ptr[u]; i < (int)E[u].size(); i++) {
			auto &it = E[u][i];

			if (it.f > 0 && dis[it.v] == dis[u] + it.w && !vis[it.v]) {
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
	pair<int, ll> flow() {
		int flow = 0; ll cost = 0;

		while (SPFA()) {
			fill_n(ptr, n, 0);
			int f = DFS(s, INT_MAX);
			flow += f;
			cost += dis[t] * f;
		}

		return { flow, cost };
	}
} flow;

const int INF = (int)1e9;
const int N = 50000 + 5;

int n, q, b[N];

void init() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> b[i];
}
void solve() {
    while (q--) {
        int m, k; cin >> m >> k;
        int s = 0, t = m*2+1, ss = m*2+2;
        flow.init(m*2+3, ss, t);
        for (int i = 1; i <= m; i++) {
            flow.add_edge(s, i*2-1, INF, 0);
            flow.add_edge(i*2-1, i*2, 1, -1);
            flow.add_edge(i*2, t, INF, 0);
            for (int j = i + 1; j <= m; j++) {
                if (b[i] >= b[j]) flow.add_edge(i*2, j*2-1, INF, 0);
            }
        }
        flow.add_edge(ss, s, k, 0);
        cout << -flow.flow().second << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
