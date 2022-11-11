#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ordered_set = tree<pair<int, int>, null_type, less_equal<pair<int, int> >, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, k; cin >> n >> k;
  ordered_set s;
  ll lsum = 0, rsum = 0;
  for (int i = 0; i < k - 1; i++) {
    int x; cin >> x;
    s.insert(x);
  }

  for (int i = k; i < n; i++) {

  }
}
