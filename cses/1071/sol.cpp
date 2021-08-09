#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll x, y;

void init() {
    cin >> x >> y;
}
void solve() {
    ll z = max(x, y);
    if (z % 2 == 1) swap(x, y);
    if (x == z) cout << z * z - (y - 1) << '\n';
    else cout << (z - 1) * (z - 1) + x << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t; cin >> t;
    while (t--) {
        init();
        solve();
    }
}
