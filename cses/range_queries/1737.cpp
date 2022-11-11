#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace segtree {
#define mid (l + r) >> 1
  struct Node {
    ll val;
    Node *lson, *rson;
    
    Node() {}
    Node(ll _val) : val(_val), lson(nullptr), rson(nullptr) {}
    Node(const Node& node) : val(node.val), lson(node.lson), rson(node.rson) {}
    void* operator new(size_t);
    void pull() {
      val = lson->val + rson->val;
    }
  } pool[18000005];
  int top = 0;
  void* Node::operator new(size_t) { return &pool[top++]; }
  
  vector<Node*> root;
  void build(int l, int r, vector<ll>& v, Node *node) {
    node->lson = new Node(0);
    node->rson = new Node(0);
    if (l + 1 == r) return void(node->val = v[l]);
    build(l, mid, v, node->lson);
    build(mid, r, v, node->rson);
    node->pull();
  }
  void init(int n, vector<ll>& v) {
    top = 0; root.clear();
    root.push_back(new Node());
    build(0, n, v, root.back());
  }
  void new_version(int k) {
    root.push_back(new Node(*root[k]));
  }
  void update(int l, int r, int q, ll v, Node* node) {
    node->lson = new Node(*(node->lson));
    node->rson = new Node(*(node->rson));
    if (l + 1 == r) return void(node->val = v);
    if (q < mid) update(l, mid, q, v, node->lson);
    else update(mid, r, q, v, node->rson);
    node->pull();
  }
  ll query(int l, int r, int ql, int qr, Node* node) {
    if (ql <= l && r <= qr) return node->val;

    if (qr <= mid) return query(l, mid, ql, qr, node->lson);
    else if (mid <= ql) return query(mid, r, ql, qr, node->rson);
    else return query(l, mid, ql, mid, node->lson) + query(mid, r, mid, qr, node->rson);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, q; cin >> n >> q;
  vector<ll> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  segtree::init(n, v);
  for (int i = 0; i < q; i++) {
    int op; cin >> op;
    if (op == 1) {
      int k, a, x; cin >> k >> a >> x; a--, k--;
      segtree::update(0, n, a, x, segtree::root[k]);
    }
    else if (op == 2) {
      int k, a, b; cin >> k >> a >> b; a--, b--, k--;
      cout << segtree::query(0, n, a, b+1, segtree::root[k]) << '\n';
    }
    else {
      int k; cin >> k; k--;
      segtree::new_version(k);
    }
  }
}
