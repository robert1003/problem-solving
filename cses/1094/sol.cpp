#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxN = (int)2e5 + 5;

int n, x[maxN];

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
}
void solve() {
    ll ans = 0;
    for (int i = 2; i <= n; i++) {
        ans += max(0, x[i - 1] - x[i]);
        x[i] = max(x[i - 1], x[i]);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
