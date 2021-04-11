#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lll = __int128;

int n, q, cnt[4], score[3];
lll C[121][121];
string s[3];

lll gcd(lll a, lll b) {
  return b ? gcd(b, a % b) : a;
}
string str(lll x) {
  string t;
  while(x > 0) t.push_back('0' + x % 10), x /= 10;
  if(t.empty()) t.push_back('0');
  reverse(t.begin(), t.end());
  return t;
}

void build() {
  for(int i = 0 ; i < 121 ; ++i) C[i][0] = 1;
  for(int i = 1 ; i < 121 ; ++i) {
    for(int j = 1 ; j < 121 ; ++j) {
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }
}
void init() {
  cin >> n >> q;
  fill(cnt, cnt + 4, 0);
  for(int i = 0 ; i < n ; ++i) cin >> s[i] >> score[i];
  for(int i = n ; i < 3 ; ++i) s[i] = s[0], score[i] = score[0];
  for(int i = 0 ; i < q ; ++i) {
    int msk = (s[2][i] == 'T') * 4 + (s[1][i] == 'T') * 2 + (s[0][i] == 'T');
    cnt[min(msk, 7 - msk)]++;
  }
}
void solve(int kase) {
  // enumerate all possible quadruples
  int c[4];
  lll tot = 0, sum[4][121] = {0};
  //cerr << cnt[0] << ' ' << cnt[1] << ' ' << cnt[2] << ' ' << cnt[3] << '\n';
  for(c[0] = 0 ; c[0] <= cnt[0] ; ++c[0]) {
    for(c[1] = 0 ; c[1] <= cnt[1] ; ++c[1]) {
      for(c[2] = 0 ; c[2] <= cnt[2] ; ++c[2]) {
        for(c[3] = 0 ; c[3] <= cnt[3] ; ++c[3]) {
          // check if c is valid
          if((cnt[0] - c[0]) + c[1] + (cnt[2] - c[2]) + c[3] != score[0]) continue;
          if((cnt[0] - c[0]) + (cnt[1] - c[1]) + c[2] + c[3] != score[1]) continue;
          if((cnt[0] - c[0]) + (cnt[1] - c[1]) + (cnt[2] - c[2]) + (cnt[3] - c[3]) != score[2]) continue;
          // calculate # of valid sequence
          //cerr << c[0] << ' ' << c[1] << ' ' << c[2] << ' ' << c[3] << '\n';
          lll tmp = 1, _C[4];
          for(int i = 0 ; i < 4 ; ++i) _C[i] = C[cnt[i]][c[i]], tmp *= _C[i];//, cerr << i << ' ' << str(_C[i]) << '\n';
          //cerr << "tmp: " << str(tmp) << '\n';
          tot += tmp;
          for(int i = 0 ; i < 4 ; ++i) sum[i][c[i]] += tmp / _C[i];
        }
      }
    }
  }
  //cerr << "tot: " << str(tot) << '\n';
  // choose ans with largest probability, num / den
  bool ans[4] = {0};
  lll num = 0;
  for(int i = 0 ; i < 4 ; ++i) {
    if(!cnt[i]) continue;
    lll yes = 0;
    for(int j = 1 ; j <= cnt[i] ; ++j) {
      yes += sum[i][j] * C[cnt[i] - 1][j - 1]; // # of cases that one question's ans is true
    }
    lll no = tot - yes;
    //cerr << i << ' ' << str(tot) << ' ' << str(yes) << ' ' << str(no) << '\n';
    ans[i] = yes > no;
    num += max(yes, no) * cnt[i];
  }
  lll g = gcd(num, tot);
  num /= g; tot /= g;
  // construct ans string
  string choice;
  for(int i = 0 ; i < q ; ++i) {
    int msk = (s[2][i] == 'T') * 4 + (s[1][i] == 'T') * 2 + (s[0][i] == 'T');
    int idx = min(msk, 7 - msk);
    if((ans[idx] && msk < 4) || (!ans[idx] && msk >= 4)) choice.push_back('T');
    else choice.push_back('F');
  }
  cout << "Case #" << kase << ": " << choice << ' ' << str(num) << '/' << str(tot) << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t, kase = 1; cin >> t;
  build();
  while(t--) {
    init();
    solve(kase++);
  }
}
