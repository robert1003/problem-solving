#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> cnt(26);
  string s; cin >> s;
  for (auto i : s) cnt[i - 'A']++;
  string ans;
  int oddcnt = 0;
  for (int i = 0; i < 26; i++) {
    if (cnt[i] & 1) {
      oddcnt++;
      continue;
    }
    for (int j = 0; j < cnt[i] / 2; j++) {
      ans.push_back('A' + i);
    }
  }
  if (oddcnt > 1) {
    cout << "NO SOLUTION\n";
  }
  else {
    if (oddcnt == 1) {
      for (int i = 0; i < 26; i++) {
        if (cnt[i] & 1) {
          for (int j = 0; j < cnt[i]; j++) {
            ans.push_back('A' + i);
          }
          break;
        }
      }
    }
    for (int i = 25; i >= 0; i--) {
      if (cnt[i] & 1) continue;
      for (int j = 0; j < cnt[i] / 2; j++) {
        ans.push_back('A' + i);
      }
    }
    cout << ans << '\n';
  }
}
