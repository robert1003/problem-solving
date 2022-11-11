#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  vector<string> board(8);
  for (int i = 0; i < 8; i++) cin >> board[i];
  
  int ans = 0;
  vector<int> now;

  auto check = [&](int r, int c) {
    if (board[r][c] == '*') return false;
    for (int pc = 0; pc < (int)now.size(); pc++) {
      int pr = now[pc];
      if (pr == r || (abs(r - pr) == abs(c - pc))) return false;
    }
    return true;
  };
  function<void(int)> dfs = [&](int col) {
    if (col == 8) {
      ans++;
      return;
    }
    for (int row = 0; row < 8; row++) {
      if (check(row, col)) {
        now.push_back(row);
        dfs(col + 1);
        now.pop_back();
      }
    }
  };
  
  dfs(0);
  cout << ans << '\n';
}
