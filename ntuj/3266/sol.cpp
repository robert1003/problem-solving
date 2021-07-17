#pragma GCC optimize ("O3,no-stack-protector,unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
#define all(x) (x).begin(),(x).end()
#define rep(a,b,c) for(int a=b;a<c;a++)
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;

struct MCMF {
	int N;
	vector<vi> ed, red;
	vector<VL> cap, flow, cost;
	vi seen;
	VL dist, pi;
	vector<pii> par;

	MCMF(int N) :
		N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap),
		seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		this->cap[from][to] = cap;
		this->cost[from][to] = cost;
		ed[from].push_back(to);
		red[to].push_back(from);
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({0, s});

		auto relax = [&](int i, ll cap, ll cost, int dir) {
			ll val = di - pi[i] + cost;
			if (cap && val < dist[i]) {
				dist[i] = val;
				par[i] = {s, dir};
				if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
				else q.modify(its[i], {-dist[i], i});
			}
		};

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (int i : ed[s]) if (!seen[i])
				relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
			for (int i : red[s]) if (!seen[i])
				relax(i, flow[i][s], -cost[i][s], 0);
		}
		rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
			totflow += fl;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				if (r) flow[p][x] += fl;
				else flow[x][p] -= fl;
		}
		rep(i,0,N) rep(j,0,N) totcost += cost[i][j] * flow[i][j];
		return {totflow, totcost};
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,0,N) if (pi[i] != INF)
				for (int to : ed[i]) if (cap[i][to])
					if ((v = pi[i] + cost[i][to]) < pi[to])
						pi[to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

const int N = 3000 + 5;
int n, a[N];

void init() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
}
void solve() {
    MCMF flow = MCMF(n * 2 + 4);
    int ssrc = 2*n+2, ssnk = 2*n+3;
    int src = 2*n, snk = 2*n+1;
    for (int i = 0; i < n; i++) {
        flow.addEdge(src, 2*i, 1, 0);
        flow.addEdge(2*i+1, snk, 1, 0);
        flow.addEdge(2*i, 2*i+1, 1, -1);

        for (int j = i + 1; j < n; j++) {
            if (abs(a[j] - a[i]) % 7 == 0 || abs(a[j] - a[i]) == 1) {
                flow.addEdge(2*i+1, 2*j, 1, 0);
            }
        }
    }
    flow.addEdge(ssrc, src, 4, 0);
    flow.addEdge(snk, ssnk, 4, 0);
    
    flow.setpi(ssrc);
    cout << -flow.maxflow(ssrc, ssnk).second << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
