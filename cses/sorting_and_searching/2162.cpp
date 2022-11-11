#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;

  vector<int> l(n), r(n);
  for (int i = 0; i < n; i++) {
    r[i] = (i + 1) % n;
    l[i] = (i - 1 + n) % n;
  }

  int now = n - 1, cnt = 0;
  while (cnt < n) {
    now = r[r[now]];
    cnt++;
    cout << now + 1 << " \n"[cnt == n];
    r[l[now]] = r[now];
    l[r[now]] = l[now];
  }
}
