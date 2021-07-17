#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 200 + 5;
const int K = 1000 + 5;
const int M = (int)1e9 + 7;

ll n, k, a[N], dp[2][N][K];

void init() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
}
void solve() {
    int cur = 0; dp[cur ^ 1][0][0] = dp[cur ^ 1][1][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            int diff = abs(a[i] - a[i - 1]);
            for (int _k = 0; _k <= k; _k++) {
                dp[cur][j][_k] = 0;
                if (_k >= diff * j) {
//                    cerr << "(" << i - 1 << ", " << j << ", " << _k - diff * j << ") = " << dp[cur ^ 1][j][_k - diff * j] << ' ';
                    dp[cur][j][_k] = (dp[cur][j][_k] + dp[cur ^ 1][j][_k - diff * j] * (j + 1) % M) % M;
                }
                if (j - 1 >= 0 && _k >= diff * (j - 1)) {
//                    cerr << "(" << i - 1 << ", " << j - 1 << ", " << _k - diff * (j - 1) << ") = " << dp[cur ^ 1][j - 1][_k - diff * (j - 1)] << ' ';
                    dp[cur][j][_k] = (dp[cur][j][_k] + dp[cur ^ 1][j - 1][_k - diff * (j - 1)]) % M;
                }
                if (j + 1 <= n && _k >= diff * (j + 1)) {
//                    cerr << "(" << i - 1 << ", " << j + 1 << ", " << _k - diff * (j + 1) << ") = " << dp[cur ^ 1][j + 1][_k - diff * (j + 1)] << ' ';
                    dp[cur][j][_k] = (dp[cur][j][_k] + dp[cur ^ 1][j + 1][_k - diff * (j + 1)] * (j + 1) % M) % M;
                }
//                cerr << '\n';
//                cerr << "dp[" << i << "][" << j << "][" << _k << "] = " << dp[cur][j][_k] << '\n';
            }
        }
        cur ^= 1;
    }
    int ans = 0;
    for (int i = 0; i <= k; i++) ans = (ans + dp[cur ^ 1][0][i]) % M;
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
