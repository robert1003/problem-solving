#include <bits/stdc++.h>
using namespace std;

int ask(int i, int j, int k) {
   cout << i << ' ' << j << ' ' << k << endl;
   int res; cin >> res;
   return res;
}
int answer(vector<int>& ans) {
  cout << ans[0];
  for(int i = 1 ; i < (int)ans.size() ; ++i) cout << ' ' << ans[i];
  cout << endl;
  int res; cin >> res;
  return res;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t, n, q; cin >> t >> n >> q;
  while(t--) {
    vector<int> ans = {1, 2, 3};
    int mid = ask(1, 2, 3);
    if(ans[0] == mid) swap(ans[0], ans[1]);
    else if(ans[2] == mid) swap(ans[1], ans[2]);

    for(int i = 4 ; i <= n ; ++i) {
      int l = 0, r = ans.size() - 1, res;
      //cerr << "start: " << l << ' ' << r << '\n';

      while(r - l + 1 > 2) {
        int ql = l + (r - l) / 3, qr = r - (r - l) / 3;
        //cerr << ql << ' ' << qr << '\n';
        res = ask(i, ans[ql], ans[qr]);
        assert(res != -1);
        if(res == ans[ql]) r = ql;
        else if(res == ans[qr]) l = qr + 1;
        else l = ql + 1, r = qr;
      }

      //cerr << "end: " << l << ' ' << r << '\n';
      if(l == r && r == ans.size() - 1) l--;
      if(l >= r) ans.insert(ans.begin() + l, i);
      else {
        res = ask(i, ans[l], ans[r]); assert(res != -1);
        if(res == ans[l]) ans.insert(ans.begin() + l, i);
        else if(res == ans[r]) ans.insert(ans.begin() + r + 1, i);
        else ans.insert(ans.begin() + r, i);
      }
      //cerr << "ans: ";
      //for(auto i : ans) cerr << i << ' ';
      //cerr << '\n';
      /*
      res = ask(i, ans[l], ans[r]); assert(res != -1);
      if(res == ans[l]) ans.insert(ans.begin() + l, i);
      else if(res == ans[r]) ans.insert(ans.begin() + r + 1, i);
      else {
        res = ask(i, ans[l], ans[l + 1]); assert(res != -1 && res != ans[l]);
        if(res == ans[l + 1]) ans.insert(ans.begin() + l + 2, i);
        else ans.insert(ans.begin() + l + 1, i);
      }
      */
    }

    assert(answer(ans) == 1);
  }
}
