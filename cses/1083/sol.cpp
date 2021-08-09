#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxN = (int)2e5 + 5;

int n, cnt[maxN];

void init() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a; cin >> a;
        cnt[a]++;
    }
}
void solve() {
    for (int i = 1; i <= n; i++) if (!cnt[i]) {
        cout << i << '\n';
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
