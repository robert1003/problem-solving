#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int INF = (int)1e9;
const int N = (1 << 20) + 5;

int n, m, t[N], msk[N], imsk[N], fix[N], bug[N];
string a[N], b[N];
int d[N], inq[N];

int SPFA(int s, int e) {
    fill(d, d + (1 << n), INF);
    d[s] = 0;
    deque<int> dq; dq.push_back(s);
    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front(); inq[u] = 0;
        for (int i = 1; i <= m; i++) {
            if (msk[i] != 0 && (msk[i] & u) != msk[i]) continue;
            if (imsk[i] != 0 && (imsk[i] & (~u)) != imsk[i]) continue;
            int v = (u & fix[i]) | bug[i];
            if (d[v] > d[u] + t[i]) {
                d[v] = d[u] + t[i];
                if (inq[v] == 0) {
                    inq[v] = 1;
                    if (d[v] < d[dq.front()]) dq.push_front(v);
                    else dq.push_back(v);
                }
            }
        }
    }

    return (d[e] == INF ? 0 : d[e]);
}

void init() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> t[i] >> a[i] >> b[i];
        for (auto c : a[i]) {
            if (c == '+') msk[i] |= 1;
            else if (c == '-') imsk[i] |= 1;
            msk[i] <<= 1, imsk[i] <<= 1;
        }
        msk[i] >>= 1, imsk[i] >>= 1;

        for (auto c : b[i]) {
            if (c == '-') fix[i] |= 1;
            else if (c == '+') bug[i] |= 1;
            fix[i] <<= 1, bug[i] <<= 1;
        }
        fix[i] >>= 1, bug[i] >>= 1;
        fix[i] = ~fix[i];

    }
}
void solve() {
    cout << SPFA((1 << n) - 1, 0) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
