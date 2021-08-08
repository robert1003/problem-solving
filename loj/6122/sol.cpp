#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct zkwflow{
    static const int N = 10000;
	struct Edge {
		int to, rev, cap, c; ll cost;
	};
	vector<Edge> g[N];
	int nv, sv, tv, ptr[N];
	bool vis[N]; ll dist[N];
	void init(int n,int s,int t){
		nv=n+1; sv=s; tv=t;
		for(int i=0;i<nv;i++) g[i].clear();
	}
	void add_edge(int a, int b, int c, ll w) {
		g[a].push_back(Edge{b,int(g[b].size()),c,c,w});
		g[b].push_back(Edge{a,int(g[a].size())-1,0,0,-w});
	}
	bool augment() { // SPFA
		for (int i = 0; i < nv; i++) {
			dist[i] = LLONG_MAX; vis[i] = false;
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
		return dist[tv] != LLONG_MAX;
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
	pair<int, ll> flow() {
		int flow = 0; ll cost = 0;
		while (augment()) {
			fill_n(ptr, nv, 0);
			int d = dfs(sv, INT_MAX);
			flow += d; cost += d * dist[tv];
		}
		return { flow, cost };
	}
}flow;


int n, m;
vector<array<int, 2> > edges;
map<int, string> inv;
vector<int> G[105];
vector<int> path;

void dfs(int u) {
    path.push_back(u);
    for (auto v : G[u]) dfs(v);
}

void init() {
    cin >> n >> m;
    map<string, int> idx;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        idx[s] = i + 1;
        inv[i + 1] = s;
    }
    for (int i = 0; i < m; i++) {
        string s, t; cin >> s >> t;
        edges.push_back({idx[s], idx[t]});
    }
}
void solve() {
    int s = 0, t = 2 * n + 1;
    flow.init(2 * n + 2, s, t);
    flow.add_edge(s, 1, 2, 0);
    flow.add_edge(2*n, t, 2, 0);
    for (int i = 1; i <= n; i++) {
        if (i == 1 || i == n) flow.add_edge(2*i-1, 2*i, 2, 0);
        else flow.add_edge(2*i-1, 2*i, 1, 0);
    }
    for (auto [u, v] : edges) {
        flow.add_edge(2*u, 2*v-1, 1, -1);
    }
    auto res = flow.flow();
    if (res.first == 0) {
        cout << "No Solution!\n";
        return;
    }
    for (int i = 1; i < n; i++) {
        for (auto &it : flow.g[2*i]) {
            if (it.c > 0 && it.cap == 0 && it.to % 2 == 1) {
                G[i].push_back((it.to + 1) / 2);
            }
        }
    }
    dfs(1);
    vector<int> ans;
    for (int i = 0; i < (int)path.size(); i++) {
        ans.push_back(path[i]);
        if (path[i] == n) break;
    }
    if (res.first == 2) {
        for (int i = (int)path.size() - 2; i >= 0; i--) {
            if (path[i] == n) break;
            ans.push_back(path[i]);
        }
    }
    ans.push_back(1);
    if (res.first == 1) cout << -res.second * 2 << '\n';
    else cout << -res.second << '\n';
    for (auto i : ans) {
        cout << inv[i] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
