#include <bits/stdc++.h>
using namespace std;

string s[100];

double inverse_sigmoid(double y) {
  return -log(1 / y - 1);
}
double sigmoid(double x) {
  return 1.0 / (1.0 + exp(-x));
}

void init() {
  for(int i = 0 ; i < 100 ; ++i) cin >> s[i];
}
void solve(int kase) {
  vector<double> Q(10000, 0.0), S(100, 0.0);
  for(int i = 0 ; i < 100 ; ++i) {
    for(int j = 0 ; j < 10000 ; ++j) {
      Q[j] += (s[i][j] - '0');
      S[i] += (s[i][j] - '0');
    }
  }
  for(int i = 0 ; i < 10000 ; ++i) Q[i] = -inverse_sigmoid(Q[i] / 100);
  for(int i = 0 ; i < 100 ; ++i) S[i] = inverse_sigmoid(S[i] / 10000);

  int mx = -1, idx = -1;
  for(int i = 0 ; i < 100 ; ++i) {
    int cnt = 0;
    for(int j = 0 ; j < 10000 ; ++j) {
      int expected = (S[i] - Q[j]) > 1;
      if(s[i][j] == '0' && expected == 1) cnt++;
    }
    if(cnt > mx) { mx = cnt; idx = i; }
  }
  cout << "Case #" << kase << ": " << idx + 1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t, p, kase = 1; cin >> t >> p;
  while(t--) {
    init();
    solve(kase++);
  }
}
