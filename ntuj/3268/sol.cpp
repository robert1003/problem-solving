#pragma GCC optimize ("O3,no-stack-protector,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxN = (int)3e5 + 1;

struct DSU {
    ll s1[maxN * 2], s2[maxN * 2], pa[maxN * 2], cnt;
    vector<pair<ll*, ll>> mem;
    vector<int> memSz;

    void init() {
        for (int i = 1; i < maxN * 2; i++) {
            s1[i] = i < maxN;
            s2[i] = i >= maxN;
            pa[i] = i;
        }
        cnt = 0;
    }
    void _set(ll &v, ll nv) {
        mem.push_back(make_pair(&v, v));
        v = nv;
    }
    int find(int x) {
        while (x != pa[x]) x = pa[x];
        return x;
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        _set(cnt, cnt - s1[x] * s2[x] - s1[y] * s2[y]);
        if (s1[x] + s2[x] < s1[y] + s2[y]) swap(x, y);
        _set(pa[y], x);
        _set(s1[x], s1[x] + s1[y]); _set(s1[y], 0);
        _set(s2[x], s2[x] + s2[y]); _set(s2[y], 0);
        _set(cnt, cnt + s1[x] * s2[x]);
        return true;
    }
    void snapshot() {
        memSz.push_back(mem.size());
    }
    void rollback() {
        while ((int)mem.size() > memSz.back()) {
            *mem.back().first = mem.back().second;
            mem.pop_back();
        }
        memSz.pop_back();
    }
};

struct Segtree {
    vector<pair<int, int>> a[maxN * 4];
    vector<ll> ans;
    DSU dsu;

    void init(int n) {
        //for (int i = 0; i <= n * 4; i++) a[i].clear();
        dsu.init();
    }
    void add(int l, int r, int ql, int qr, pair<int, int> v, int o=0) {
        if (ql <= l && r <= qr) {
            a[o].push_back(v); return;
        }
        
        int mid = (l + r) >> 1;
        if (qr <= mid) return add(l, mid, ql, qr, v, o * 2 + 1);
        else if (mid <= ql) return add(mid, r, ql, qr, v, o * 2 + 2);
        else {
            add(l, mid, ql, mid, v, o * 2 + 1);
            add(mid, r, mid, qr, v, o * 2 + 2);
        }
    }
    void traverse(int l, int r, int o=0) {
        dsu.snapshot();
        for (auto p : a[o]) dsu.merge(p.first, p.second + maxN);
        
        if (l + 1 < r) {
            int mid = (l + r) >> 1;
            traverse(l, mid, o * 2 + 1);
            traverse(mid, r, o * 2 + 2);
        } else {
            ans.push_back(dsu.cnt);
        }

        dsu.rollback();
    }
} segtree;

int q;
vector<pair<int, int>> qs;

void init() {
    cin >> q; qs.resize(q);
    for (int i = 0; i < q; i++) cin >> qs[i].first >> qs[i].second;
}
void solve() {
    segtree.init(q + 1);
    map<pair<int, int>, int> last;
    for (int i = 0; i < q; i++) {
        if (last.count(qs[i]) == 0) last[qs[i]] = i;
        else {
            //cerr << last[qs[i]] << ' ' << i << ' ' << qs[i].first << ' ' << qs[i].second << '\n';
            segtree.add(0, q + 1, last[qs[i]], i, qs[i]);
            last.erase(qs[i]);
        }
    }
    for (auto i : last) {
        //cerr << i.second << ' ' << q << ' ' << i.first.first << ' ' << i.first.second << '\n';
        segtree.add(0, q + 1, i.second, q, i.first);
    }
    segtree.traverse(0, q + 1);
    for (int i = 0; i < (int)segtree.ans.size() - 1; i++) {
        cout << segtree.ans[i] << " ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    init();
    solve();
}
