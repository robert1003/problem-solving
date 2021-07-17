#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 300 + 5;

int n, m;
deque<char> a[N][N], b[N][N];
vector<tuple<int, int, int, int>> ans;

void move(int i1, int j1, int i2, int j2) {
    assert (i1 != i2 || j1 != j2);
    assert (i1 == i2 || j1 == j2);
    ans.push_back(make_tuple(i1, j1, i2, j2));
    a[i2][j2].push_front(a[i1][j1].back());
    a[i1][j1].pop_back();
}
void debug() {
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        for (int k = 0; k < (int)a[i][j].size(); k++) cerr << a[i][j][k];
        if (a[i][j].size() == 0) cerr << "*";
        cerr << " \n"[j == m - 1];
    }
    cerr << '\n';
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        string s; cin >> s; a[i][j] = deque<char>(s.begin(), s.end());
    }
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        string s; cin >> s; reverse(s.begin(), s.end());
        b[i][j] = deque<char>(s.begin(), s.end());
    }
}
void solve() {
    for (int j = 1; j < m; j++) while (a[0][j].size()) move(0, j, 0, 0);
    for (int i = 1; i < n; i++) while (a[i][0].size()) move(i, 0, 0, 0);
    for (int i = 1; i < n; i++) for (int j = 1; j < m; j++) while (a[i][j].size()) {
        if (a[i][j].back() == '0') move(i, j, i, 0);
        else move(i, j, 0, j);
    }
    for (int j = 1; j < m - 1; j++) while (a[0][j].size()) move(0, j, 0, m - 1);
    for (int i = 1; i < n - 1; i++) while (a[i][0].size()) move(i, 0, n - 1, 0);
    while (a[0][0].size()) {
        if (a[0][0].back() == '0') move(0, 0, n - 1, 0);
        else move(0, 0, 0, m - 1);
    }
    //debug();

    swap(a, b);
    int sz = ans.size();

    for (int j = 1; j < m; j++) while (a[0][j].size()) move(0, j, 0, 0);
    for (int i = 1; i < n; i++) while (a[i][0].size()) move(i, 0, 0, 0);
    for (int i = 1; i < n; i++) for (int j = 1; j < m; j++) while (a[i][j].size()) {
        if (a[i][j].back() == '0') move(i, j, i, 0);
        else move(i, j, 0, j);
    }
    for (int j = 1; j < m - 1; j++) while (a[0][j].size()) move(0, j, 0, m - 1);
    for (int i = 1; i < n - 1; i++) while (a[i][0].size()) move(i, 0, n - 1, 0);
    while (a[0][0].size()) {
        if (a[0][0].back() == '0') move(0, 0, n - 1, 0);
        else move(0, 0, 0, m - 1);
    }
    //debug();

    // print ans
    reverse(ans.begin() + sz, ans.end());
//    cerr << sz << '\n';
    cout << ans.size() << '\n';
    for (int _ = 0; _ < (int)ans.size(); _++) {
        auto t = ans[_];
        int i = get<0>(t), j = get<1>(t), k = get<2>(t), l = get<3>(t);
        if (_ < sz) cout << i+1 << ' ' << j+1 << ' ' << k+1 << ' ' << l+1 << '\n';
        else cout << k+1 << ' ' << l+1 << ' ' << i+1 << ' ' << j+1 << '\n';

    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
