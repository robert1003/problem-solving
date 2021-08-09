#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n;

void init() {
    cin >> n;
}
void solve() {
    for (ll i = 1; i <= n; i++) {
        cout << (i * i) * (i * i - 1) / 2 - (i - 1) * (i - 2) * 4 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
