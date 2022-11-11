#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Pt {
  ll x, y;

  Pt () {}
  Pt (ll _x, ll _y) : x(_x), y(_y) {}
  friend istream& operator>>(istream& in, Pt& p) {
    in >> p.x >> p.y;
    return in;
  }
  friend ostream& operator<<(ostream& out, Pt& p) {
    out << '(' << p.x << ',' << p.y << ')';
    return out;
  }

  Pt operator+(const Pt& p) const {
    return Pt(x+p.x, y+p.y);
  }
  Pt operator-(const Pt& p) const {
    return Pt(x-p.x, y-p.y);
  }
  ll operator^(const Pt& p) const {
    return x*p.y - y*p.x;
  }
  ll operator*(const Pt& p) const {
    return x*p.x + y*p.y;
  }
  bool operator<(const Pt& p) const {
    return (x < p.x) || (x == p.x && y < p.y);
  }
};

ll sgn(ll x) {
  return (x>0) - (x<0);
}
ll ori(Pt& o, Pt& a, Pt& b) {
  return sgn((a-o)^(b-o));
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<Pt> pts(n);
  for (int i = 0; i < n; i++) cin >> pts[i];

  vector<Pt> ans;
  vector<Pt> cur;
  
  sort(pts.begin(), pts.end());
  for (int i = 0; i < n; i++) {
    while (cur.size() >= 2 && ori(cur[cur.size()-2], cur[cur.size()-1], pts[i]) > 0) {
      cur.pop_back();
    }
    
    cur.push_back(pts[i]);
  }

  ans = cur;
  cur = vector<Pt>();
  reverse(pts.begin(), pts.end());
  for (int i = 0; i < n; i++) {
    while (cur.size() >= 2 && ori(cur[cur.size()-2], cur[cur.size()-1], pts[i]) > 0) {
      cur.pop_back();
    }

    cur.push_back(pts[i]);
  }
  for (int i = 1; i < cur.size()-1; i++)
    ans.push_back(cur[i]);

  cout << ans.size() << '\n';
  for (auto pt : ans) {
    cout << pt.x << ' ' << pt.y << '\n';
  }
}
