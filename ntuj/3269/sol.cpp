#pragma GCC optimize ("O3,no-stack-protector,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxK = (int)1e6 + 5;
const int M = (int)1e9 + 7;

ll n, k, f[maxK], inv[maxK];

ll powmod(ll a, ll b) {
    if (!b) return 1;
    ll ans = powmod(a, b >> 1);
    ans = ans * ans % M;
    if (b & 1) ans = ans * a % M;
    return ans;
}
inline ll getmod(ll x, ll flag) {
    if (!flag) return (x >= 0 ? x : x + M);
    if (x < 0) x += M;
    return powmod(x, M - 2);
    /*
    assert (x != 0);
    if (abs(x) >= k + 1) return powmod(
    if (x > 0) return inv[x];
    else return (-inv[-x] + M);
    */
}

void init() {
    cin >> n >> k;
    f[0] = 0;
    for (int i = 1; i <= k + 1; i++) f[i] = (f[i - 1] + powmod(i, k)) % M;
}
void solve() {
    if (n <= k + 1) {
        cout << f[n] << '\n';
        return;
    }

    ll base = 1;
    for (int i = 1; i <= k + 1; i++) base = (base * getmod(n - i, 0) % M * getmod(0 - i, 1) % M);

    ll ans = 0;
    for (int i = 1; i <= k + 1; i++) {
        base = base * getmod(n - (i - 1), 0) % M * getmod(n - i, 1) % M;
        base = base * getmod((i - 1) - (k + 1), 0) % M * getmod(i, 1) % M;
        ans = (ans + f[i] * base % M) % M;
    }

    cout << ans << '\n';
}


int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
