#pragma GCC optimize ("O3,no-stack-protector,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

struct Node {
  Node *l, *r;
  int val, sz;
  Node(const int _val) : l(nullptr), r(nullptr), val(_val), sz(1) {}

  void pull() {
    sz = 1;
    if (l) sz += l->sz;
    if (r) sz += r->sz;
  }
  void push() {
  }
};

inline int size(Node *o) {
  return o ? o->sz : 0;
}

mt19937 rng(880301);
uniform_int_distribution<> gen(0, INT_MAX);

Node *merge(Node *a, Node *b) {
  if (!a) return b;
  if (!b) return a;
  static int x;
  if (gen(rng) % (a->sz + b->sz) < a->sz) {
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

void split(Node *o, Node *&a, Node *&b, int k) {
  if (!o) a = b = nullptr;
  else {
    o->push();
    if (k <= size(o->l)) {
      b = o;
      split(o->l, a, b->l, k);
    }
    else {
      a = o;
      split(o->r, a->r, b, k - size(o->l) - 1);
    }
    o->pull();
  }
}

Node *insert(Node *root, int val, int k) {
  Node *a, *b;
  split(root, a, b, k);
  Node *cur = new Node(val);
  a = merge(a, cur);
  return merge(a, b);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  Node* root = nullptr;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    root = insert(root, x, i);
  }
  for (int i = 0; i < n; i++) {
    int k; cin >> k;
    Node *a1, *a2, *b;
    split(root, a1, b, k);
    split(a1, a1, a2, k - 1);
    root = merge(a1, b);
    cout << a2->val << " \n"[i == n - 1];
    delete a2;
  }
}
