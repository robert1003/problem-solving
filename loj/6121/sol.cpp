#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 100 + 5;
int n, m, p, k, s, walls[N][4], keys[N][4];

void init() {
    cin >> n >> m >> p >> k;
    for (int i = 0; i < k; i++) {
        int x[2], y[2], g;
        cin >> x[0] >> y[0] >> x[1] >> y[1] >> g;
        walls[ID(x[0], y[0])][DIRC(x[0], y[0], x[1], y[1])] |= 1 << g;
        walls[ID(x[1], y[1])][DIRC(x[1], y[1], x[0], y[0])] |= 1 << g;
    }
}
void solve() {
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
