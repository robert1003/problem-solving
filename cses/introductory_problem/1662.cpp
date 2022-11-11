#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
vector<int> v;
vector<int> modl, modr;
vector<int> cnt;

ll count(int l, int r) {
  if (l == r) {
    modl[l] = modr[l] = ((v[l] % n) + n) % n;
    return modl[l] == 0;
  }
  int mid = l + (r - l) / 2;
  ll ans = count(l, mid) + count(mid + 1, r);

  for (int i = mid+1; i <= r; i++) {
    cnt[modl[i]]++;
  }
  for (int i = l; i <= mid; i++) {
    ans += cnt[(n - modr[i]) % n];
  }
  for (int i = mid+1; i <= r; i++) {
    cnt[modl[i]]--;
  }
  
  for (int i = mid+1; i <= r; i++) {
    modl[i] = (modl[i - 1] + v[i]) % n;
    if (modl[i] < 0) modl[i] += n;
  }
  for (int i = mid; i >= l; i--) {
    modr[i] = (modr[i + 1] + v[i]) % n;
    if (modr[i] < 0) modr[i] += n;
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  modl.resize(n); fill(modl.begin(), modl.end(), 0);
  modr.resize(n); fill(modr.begin(), modr.end(), 0);
  cnt.resize(n); fill(cnt.begin(), cnt.end(), 0);
  cout << count(0, n - 1) << '\n';
}
