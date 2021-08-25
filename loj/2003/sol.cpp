#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = double;

const ld eps = 1e-8;

struct zkwflow {
	static const int maxN = 10000;
	struct Edge { int v, f, re; ld w; };
	int n, s, t, ptr[maxN];
	bool vis[maxN]; ld dis[maxN];
	vector<Edge> E[maxN];

	void init(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		for (int i = 0; i < n; i++) E[i].clear();
	}
	void add_edge(int u, int v, int f, ld w) {
		E[u].push_back({v, f, (int)E[v].size(), w});
		E[v].push_back({u, 0, (int)E[u].size()-1, -w});
	}
	bool SPFA() {
		fill_n(dis, n, 1e20);
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

		return dis[t] < 1e20;
	}
	int DFS(int u, int nf) {
		if (u == t) return nf;
		int res = 0; vis[u] = true;
		for (int &i = ptr[u]; i < (int)E[u].size(); i++) {
			auto &it = E[u][i];

			if (it.f > 0 && abs(dis[it.v] - dis[u] - it.w) < eps && !vis[it.v]) {
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
	pair<int, ld> flow() {
		int flow = 0; ld cost = 0;

		while (SPFA()) {
			fill_n(ptr, n, 0);
			int f = DFS(s, INT_MAX);
			flow += f;
			cost += dis[t] * f;
		}

		return { flow, cost };
	}
} flow;


const int N = 100 + 5;

int n, a[N][N], b[N][N];

bool ok(ld x) {
    int s = 0, t = n*2+1;
    flow.init(n*2 + 2, s, t);
    for (int i = 1; i <= n; i++) {
        flow.add_edge(s, i, 1, 0);
        for (int j = 1; j <= n; j++) {
            flow.add_edge(i, j + n, 1, -(ld)a[i][j] + x * b[i][j]);
        }
        flow.add_edge(i + n, t, 1, 0);
    }
    return flow.flow().second > eps;
}

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> a[i][j];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> b[i][j];
    }
}
void solve() {
    ld l = 0, r = 1e6;
    while (r - l > eps) {
        ld mid = (l + r) / 2;
        if (ok(mid)) r = mid;
        else l = mid;
    }
    cout << fixed << setprecision(6) << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
