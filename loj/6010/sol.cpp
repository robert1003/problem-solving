#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct zkwflow{
    static const int N = 10000;
    static const ll LLINF = LLONG_MAX;
	struct Edge {
		int to, rev, cap; ll cost;
	};
	vector<Edge> g[N];
	int nv, sv, tv, ptr[N];
	bool vis[N]; ll dist[N];
	void init(int n,int s,int t){
		nv=n+1; sv=s; tv=t;
		for(int i=0;i<nv;i++) g[i].clear();
	}
	void add_edge(int a, int b, int c, ll w) {
		g[a].push_back(Edge{b,int(g[b].size()),c,w});
		g[b].push_back(Edge{a,int(g[a].size())-1,0,-w});
	}
	bool augment() { // SPFA
		for (int i = 0; i < nv; i++) {
			dist[i] = LLINF; vis[i] = false;
		}
		dist[sv] = 0;
		vector<int> que = { sv };
		for (int i = 0; i < int(que.size()); i++) {
			int v = que[i];
			vis[v] = false;
			for (auto& e : g[v]) {
				if (e.cap == 0 || dist[e.to] <= dist[v] + e.cost)
					continue;
				dist[e.to] = dist[v] + e.cost;
				if (!vis[e.to]) {
					vis[e.to] = true;
					que.push_back(e.to);
				}
			}
		}
		return dist[tv] != LLINF;
	}
	int dfs(int v, int r) {
		if (v == tv) return r;
		vis[v] = true;
		int res = 0;
		for (int& i = ptr[v]; i < int(g[v].size()); i++) {
			Edge& e = g[v][i];
			if (e.cap == 0 || dist[e.to] != dist[v] + e.cost || vis[e.to])
				continue;
			int d = dfs(e.to, min(r - res, e.cap));
			res += d; e.cap -= d;
			g[e.to][e.rev].cap += d;
			if (res == r) {
				vis[v] = false;
				break;
			}
		}
		return res;
	}
	pair<int, ll> solve() {
		int flow = 0; ll cost = 0;
		while (augment()) {
			fill_n(ptr, nv, 0);
			int d = dfs(sv, INT_MAX);
			flow += d; cost += d * dist[tv];
		}
		return { flow, cost };
	}
}flow;


const int INF = (int)1e9;

int m, n;
vector<int> v[25], idx[25];

void init() {
    cin >> m >> n;
    for (int i = 1, j = m, id = 1; i <= n; i++, j++) {
        v[i].resize(j); idx[i].resize(j);
        for (int k = 0; k < j; k++) cin >> v[i][k], idx[i][k] = id++;
    }
}
void solve() {
    int tot = (m + m + n - 1) * n / 2;
    int s = 0, t = tot * 2 + 2;
    // 1.
    flow.init(tot * 2 + 2, s, t);
    for (int i = 1, cnt = m; i <= n; i++, cnt++) {
        for (int j = 0; j < cnt; j++) {
            flow.add_edge(idx[i][j]*2-1, idx[i][j]*2, 1, 0);
            if (i == 1) flow.add_edge(s, idx[i][j]*2-1, INF, -v[i][j]);
            if (i == n) flow.add_edge(idx[i][j]*2, t, INF, 0);
            else {
                flow.add_edge(idx[i][j]*2, idx[i+1][j]*2-1, INF, -v[i+1][j]);
                flow.add_edge(idx[i][j]*2, idx[i+1][j+1]*2-1, INF, -v[i+1][j+1]);
            }
        }
    }
    cout << -flow.solve().second << '\n';

    // 2.
    s = 0, t = tot + 1;
    flow.init(tot + 2, s, t);
    for (int i = 1, cnt = m; i <= n; i++, cnt++) {
        for (int j = 0; j < cnt; j++) {
            if (i == 1) flow.add_edge(s, idx[i][j], 1, -v[i][j]);
            if (i == n) flow.add_edge(idx[i][j], t, INF, 0);
            else {
                flow.add_edge(idx[i][j], idx[i+1][j], 1, -v[i+1][j]);
                flow.add_edge(idx[i][j], idx[i+1][j+1], 1, -v[i+1][j+1]);
            }
        }
    }
    cout << -flow.solve().second << '\n';

    // 3.
    s = 0, t = tot + 1;
    flow.init(tot + 2, s, t);
    for (int i = 1, cnt = m; i <= n; i++, cnt++) {
        for (int j = 0; j < cnt; j++) {
            if (i == 1) flow.add_edge(s, idx[i][j], 1, -v[i][j]);
            if (i == n) flow.add_edge(idx[i][j], t, INF, 0);
            else {
                flow.add_edge(idx[i][j], idx[i+1][j], INF, -v[i+1][j]);
                flow.add_edge(idx[i][j], idx[i+1][j+1], INF, -v[i+1][j+1]);
            }
        }
    }
    cout << -flow.solve().second << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
