#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
  Node *l, *r;
  int sz, pri;
  pair<int, int> val;
  Node(pair<int, int> _v, int _p):l(nullptr), r(nullptr), sz(1), pri(_p), val(_v) {}

  void pull() {
    sz = 1;
    if (l) sz += l->sz;
    if (r) sz += r->sz;
  }
  void push() {}
};

mt19937 rng(880301);
uniform_int_distribution<> gen(0, INT_MAX);

Node *merge(Node *a, Node *b) {
  if (!a) return b;
  if (!b) return a;
  if (a->pri > b->pri) {
    a->push();
    a->r = merge(a->r, b);
    a->pull();
    return a;
  }
  else {
    b->push();
    b->l = merge(a, b->l);
    b->pull();
    return b;
  }
}

void split(Node *o, Node *&a, Node *&b, pair<int, int> key) {
  if (!o) a = b = nullptr;
  else {
    o->push();
    if (key < o->val) {
      b = o;
      split(o->l, a, b->l, key);
    }
    else {
      a = o;
      split(o->r, a->r, b, key);
    }
    o->pull();
  }
}

Node* insert(Node *o, pair<int, int> key) {
  Node *a, *b;
  split(o, a, b, key);
  Node *cur = new Node(key, gen(rng));
  a = merge(a, cur);
  return merge(a, b);
}

Node *remove(Node *o, pair<int, int> key) {
  Node *a, *b;
  split(o, a, b, key);
  pair<int, int> pkey = key;
  pkey.second--;
  Node *a1, *a2;
  split(a, a1, a2, pkey);
  delete a2;
  return merge(a1, b);
}

void print(Node *o) {
  if (o->l) print(o->l);
  cerr << "(" << o->val.first << "," << o->val.second << ") ";
  if (o->r) print(o->r);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<int> salary(n);
  Node *root = nullptr;
  for (int i = 0; i < n; i++) {
    cin >> salary[i];
    root = insert(root, {salary[i], i});
  }
  for (int i = 0; i < q; i++) {
    char op; cin >> op;
    if (op == '?') {
      int l, r; cin >> l >> r;
      Node *a, *b, *c;
      split(root, a, b, {l, 0});
      split(b, b, c, {r, n});
      cout << (b ? b->sz : 0) << '\n';
      b = merge(b, c);
      root = merge(a, b);
    }
    else {
      int k, x; cin >> k >> x;
      root = remove(root, {salary[k - 1], k - 1});
      salary[k - 1] = x;
      root = insert(root, {salary[k - 1], k - 1});
    }
  }
}
