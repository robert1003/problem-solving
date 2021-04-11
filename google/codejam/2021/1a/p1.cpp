#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
string x[100 + 5], ans[100 + 5];

int cmp(string& s1, string& s2) {
  if(s1.size() < s2.size()) return -1;
  else if(s1.size() > s2.size()) return 1;
  else {
    for(int i = 0 ; i < (int)s1.size() ; ++i) {
      if(s1[i] == s2[i]) continue;
      else return s1[i] < s2[i] ? -1 : 1;
    }
    return 0;
  }
}

void init() {
  cin >> n;
  for(int i = 1 ; i <= n ; ++i) cin >> x[i];
}
void solve(int kase) {
  ans[1] = x[1];
  for(int i = 2 ; i <= n ; ++i) {
    ans[i] = x[i];
    if(cmp(ans[i], ans[i - 1]) <= 0) {
      int dif = -1;
      for(int j = 0 ; j < (int)ans[i].size() ; ++j) {
        if(ans[i][j] == ans[i - 1][j]) continue;
        else {
          dif = j;
          break;
        }
      }

      if(ans[i].size() == ans[i - 1].size()) ans[i].push_back('0');
      else if(ans[i].size() < ans[i - 1].size()) {
        if(dif == -1) {
          int nine_pos = ans[i - 1].size();
          while(nine_pos - 1 >= ans[i].size() && ans[i - 1][nine_pos - 1] == '9') nine_pos--;
          if(ans[i].size() == nine_pos) {
            for(int j = ans[i].size() ; j <= ans[i - 1].size() ; ++j) ans[i].push_back('0');
          }
          else {
            for(int j = ans[i].size() ; j < nine_pos - 1 ; ++j) ans[i].push_back(ans[i - 1][j]);
            ans[i].push_back(ans[i - 1][nine_pos - 1] + 1);
            for(int j = nine_pos ; j < ans[i - 1].size() ; ++j) ans[i].push_back('0');
          }
        }
        else {
          while(ans[i].size() < ans[i - 1].size()) ans[i].push_back('0');
          if(ans[i][dif] < ans[i - 1][dif]) ans[i].push_back('0');
        }
      }
    }
  }
  int sum = 0;
  for(int i = 1 ; i <= n ; ++i) {
    sum += ans[i].size() - x[i].size();
  }
  cout << "Case #" << kase << ": " << sum << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t, kase = 1; cin >> t;
  while(t--) {
    init();
    solve(kase++);
  }
}
