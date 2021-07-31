#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct zkwflow{
    static const int N = 10000;
    static const ll LLINF = INT64_MAX;
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

const int INF = INT_MAX;
int n, P, M, F, N, S, need[1005];

void init() {
    cin >> n >> P >> M >> F >> N >> S;
    for (int i = 1; i <= n; i++) cin >> need[i];
}
void solve() {
    int s = 0, t = n * 2 + 1;
    flow.init(n * 2 + 2, s, t);

    for (int i = 1; i <= n; i++) {
        flow.add_edge(s, i * 2 - 1, need[i], 0);
        flow.add_edge(i * 2, t, need[i], 0);
        flow.add_edge(s, i * 2, INF, P);
        if (i < n) flow.add_edge(i * 2 - 1, (i + 1) * 2 - 1, INF, 0);
        if (i + M <= n) flow.add_edge(i * 2 - 1, (i + M) * 2, INF, F);
        if (i + N <= n) flow.add_edge(i * 2 - 1, (i + N) * 2, INF, S);
    }

    auto ans = flow.solve();
    cout << ans.second << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
