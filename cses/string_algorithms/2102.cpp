#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct AC_automata {
  vector<array<int, 26> > next;
  vector<int> fail;
  vector<bool> isleaf;
  vector<vector<int>> leaf_idx;
  int root = 0, cnt = 0;

  int new_node() {
    array<int, 26> tmp; fill(tmp.begin(), tmp.end(), -1);
    next.push_back(move(tmp));
    fail.push_back(0);
    isleaf.push_back(0);
    leaf_idx.push_back({});
    return cnt++;
  }
  void init() {
    root = new_node();
  }
  void insert(string &s, int idx) {
    int cur = 0;
    for (auto c : s) {
      if (next[cur][c - 'a'] == -1) {
        next[cur][c - 'a'] = new_node();
      }
      cur = next[cur][c - 'a'];
    }
    isleaf[cur] = true;
    leaf_idx[cur].push_back(idx);
  }
  void build_fail() {
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
      int cur = q.front(); q.pop();
      for (int i = 0; i < 26; i++) {
        if (next[cur][i] != -1) {
          int f = fail[cur];
          while (f != root && next[f][i] == -1) f = fail[f];
          if (cur != root && next[f][i] != -1) f = next[f][i];
          fail[next[cur][i]] = f;
          q.push(next[cur][i]);
          isleaf[next[cur][i]] = isleaf[next[cur][i]] | isleaf[f];
        }
      }
    }
  }
  void print() {
    for (int i = 0; i < cnt; i++) {
      cout << i << ' ';
      for (int j = 0; j < 26; j++) if (next[i][j] != -1) cout << char('a' + j) << ' ';
      cout << '\n';
      cout << "leaf " << isleaf[i] << " fail " << fail[i] << '\n';
    }
  }
  void walk(string &s, vector<int>& visit) {
    int cur = root;
    vector<int> tag(cnt, 0);
    for (int i = 0; i < s.size(); i++) {
      while (cur != root && next[cur][s[i] - 'a'] == -1) cur = fail[cur];
      if (next[cur][s[i] - 'a'] != -1) cur = next[cur][s[i] - 'a'];

      tag[cur] = isleaf[cur];
    }

    for (int i = 0; i < cnt; i++) if (tag[i]) {
      int cur = i;
      while (isleaf[cur]) {
        for (auto j : leaf_idx[cur]) visit[j] = 1;
        tag[cur] = 0;
        cur = fail[cur];
      }
    }
  }
} ac;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  string s; cin >> s;
  int k; cin >> k;
  ac.init();
  for (int i = 0; i < k; i++) {
    string p; cin >> p;
    ac.insert(p, i);
  }
  ac.build_fail();
  vector<int> visit(k, 0);
  ac.walk(s, visit);
  for (auto i : visit) cout << (i ? "YES" : "NO") << '\n';
}
