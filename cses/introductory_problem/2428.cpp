#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, k; cin >> n >> k;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  vector<int> x = v;
  sort(x.begin(), x.end());
  x.resize(unique(x.begin(), x.end()) - x.begin());
  for (int i = 0; i < n; i++)
    v[i] = lower_bound(x.begin(), x.end(), v[i]) - x.begin();

  ll ans = 0;
  vector<int> cnt(x.size(), 0);
  function<void(int,int)> solve = [&](int l, int r) {
    if (l == r) return void(ans++);
    int mid = l + (r - l) / 2;
    solve(l, mid);
    solve(mid+1, r);

    cnt[v[mid]]++;
    int cr = mid, uniq_cnt = 1;
    while (cr < r) {
      if (!cnt[v[cr + 1]]) {
        if (uniq_cnt == k) break;
        else cr++, uniq_cnt++, cnt[v[cr]]++;
      }
      else cnt[v[++cr]]++;
    }
    ans += cr - mid;

    for (int cl = mid-1; cl >= l; cl--) {
      if (!cnt[v[cl]]) uniq_cnt++;
      cnt[v[cl]]++;
      while (cr > mid && uniq_cnt > k) {
        cnt[v[cr]]--;
        if (!cnt[v[cr]]) uniq_cnt--;
        cr--;
      }
      ans += cr - mid;
    }

    for (int i = l; i <= cr; i++) cnt[v[i]]--;
  };
  solve(0, n-1);
  cout << ans << '\n';
}
