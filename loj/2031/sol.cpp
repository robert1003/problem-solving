#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct zkwflow {
	static const int maxN = 10000;
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
            if (cost + dis[t] * f > 0) f = abs(cost / dis[t]);
			flow += f;
            cost += dis[t] * f;
		}

		return { flow, cost };
	}
} flow;

const int N = 200 + 5;
const int INF = (int)1e9;

int n, a[N], b[N], c[N], pw[N];

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) cin >> c[i];

    for (int i = 1; i <= n; i++) {
        int sum = 0, x = a[i];
        for (int p = 2; p <= x; p++) {
            while (x > 1 && x % p == 0) x /= p, sum++;
            if (x == 1) break;
        }
        pw[i] = sum;
    }
}
void solve() {
    int s = 0, t = n*2+1;
    flow.init(n*2+2, s, t);
    for (int i = 1; i <= n; i++) {
        if (pw[i] % 2 == 0) flow.add_edge(s, i, b[i], 0);
        else flow.add_edge(i + n, t, b[i], 0);
        for (int j = i + 1; j <= n; j++) {
            int mn = min(a[i], a[j]), mx = max(a[i], a[j]);
            if (mx % mn == 0 && abs(pw[i] - pw[j]) == 1) {
                if (pw[j] % 2) flow.add_edge(i, j + n, INF, -(ll)c[i]*c[j]);
                else flow.add_edge(j, i + n, INF, -(ll)c[i]*c[j]);
            }
        }
    }
    cout << flow.flow().first << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
