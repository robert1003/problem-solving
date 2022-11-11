#pragma GCC optimize ("O3,no-stack-protector,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace segtree {
#define mid (l + r) >> 1
  struct Node {
    int val;
    Node *lson, *rson;

    Node (int _val=INT_MAX) : val(_val), lson(nullptr), rson(nullptr) {}
    void pull() {
      val = INT_MAX;
      if (lson) val = min(val, lson->val);
      if (rson) val = min(val, rson->val);
    }
    void* operator new(size_t size);
  };
  Node *root = nullptr;
  const int maxn = 8000005;
  Node mempool[maxn];
  int top = 0;
  void* Node::operator new(size_t size) { 
    assert(top < maxn);
    return &mempool[top++]; 
  }

  void init() {
    root = new Node();
  }
  void update(int l, int r, int q, int v, Node *&node=root) {
    if (!node) node = new Node();
    if (l + 1 == r) return void(node->val = v);
    if (q < mid) update(l, mid, q, v, node->lson);
    else update(mid, r, q, v, node->rson);
    node->pull();
  }
  int query(int l, int r, int ql, int qr, Node *&node=root) {
    if (!node) return INT_MAX;
    if (ql <= l && r <= qr) return node->val;
    if (qr <= mid) return query(l, mid, ql, qr, node->lson);
    else if (mid <= ql) return query(mid, r, ql, qr, node->rson);
    return min(query(l, mid, ql, mid, node->lson), query(mid, r, mid, qr, node->rson));
  }
  void print(int l, int r, Node *&node=root) {
    if (node)
      cerr << l << ' '  << r << ' ' << node->val << '\n';
    if (node->lson)
      print(l, mid, node->lson);
    if (node->rson)
      print(mid, r, node->rson);
  }
}

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, set<int>> idx;
gp_hash_table<int, int> sz;

inline void rit(int &x) {
  char c = getchar_unlocked();
  while (!isdigit(c)) c = getchar_unlocked();
  x = c - '0';
  while (isdigit(c=getchar_unlocked())) x = x * 10 + (c - '0');
}
char buff[20];
inline void wit(int x) {
  if (x == 0) {
    putchar('0');
    return;
  }

  int i;
  for (i = 0; x > 0; i++) {
    buff[i] = '0' + (x % 10);
    x /= 10;
  }
  for (int j = i - 1; j >= 0; --j) {
    putchar_unlocked(buff[j]);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, m, mx = (int)1e9 + 1; 
  //cin >> n >> m;
  rit(n); rit(m);
  segtree::init();
  for (int i = 0; i < n; i++) {
    int x; rit(x);//cin >> x;
    if (idx[x].empty() || i < *idx[x].begin())
      segtree::update(0, mx, x, i);
    idx[x].insert(i);
    sz[i] = x;
  }
  auto solve = [&]() {
      int qsz; rit(qsz);//cin >> qsz;
      int id = segtree::query(0, mx, qsz, mx);
      int nsz = sz[id];
      int remain = nsz - qsz;
      // remove
      idx[nsz].erase(id);
      if (idx[nsz].empty() || id < *idx[nsz].begin())
        segtree::update(0, mx, nsz, (idx[nsz].empty() ? INT_MAX : *idx[nsz].begin()));
      // insert
      if (remain > 0) {
        sz[id] = remain;
        if (idx[remain].empty() || id < *idx[remain].begin())
          segtree::update(0, mx, remain, id);
        idx[remain].insert(id);
      }
      // return ans
      if (id == INT_MAX) return 0;
      else return id + 1;
  };
  for (int i = 0; i < m - 1; i++) {
    wit(solve());
    putchar_unlocked(' ');
    //cout << solve() << ' ';
  }
  wit(solve());
  putchar_unlocked('\n');
  //cout << solve() << '\n';
  //segtree::end();
}
