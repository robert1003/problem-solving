#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;

void init() {
    cin >> n;
}
void solve() {
    if (n == 1) cout << "1\n";
    else if (n == 2 || n == 3) cout << "NO SOLUTION\n";
    else if (n == 4) cout << "3 1 4 2\n";
    else {
        cout << "1";
        for (int i = 3; i <= n; i += 2) cout << ' ' << i;
        for (int i = 2; i <= n; i += 2) cout << ' ' << i;
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
