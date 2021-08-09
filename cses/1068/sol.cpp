#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n;

void init() {
    cin >> n;
}
void solve() {
    cout << n;
    while (n > 1) {
        if (n % 2 == 0) n /= 2;
        else n = n * 3 + 1;
        cout << ' ' << n;
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
