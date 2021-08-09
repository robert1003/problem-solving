#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s;

void init() {
    cin >> s;
}
void solve() {
    int cnt = 0, ans = 1;
    char now = '-';
    for (auto c : s) {
        if (c != now) {
            cnt = 1, now = c;
        }
        else cnt++, ans = max(ans, cnt);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
