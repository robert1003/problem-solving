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
  Pt operator/(const ll c) const {
    return Pt(x/c, y/c);
  }
  ll operator*(const Pt& p) const {
    return x*p.x + y*p.y;
  }
  ll operator^(const Pt& p) const {
    return x*p.y - y*p.x;
  }
};

ll area2(vector<Pt>& v) {
  int n = (int)v.size()-1;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans += (v[i] ^ v[i+1]);
  }
  return abs(ans);
}
ll pts_on_boundary(vector<Pt>& v) {
  int n = (int)v.size()-1;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    Pt diff = v[i+1] - v[i];
    if (diff.x == 0) {
      ans += abs(diff.y);
    }
    else if (diff.y == 0) {
      ans += abs(diff.x);
    }
    else {
      ll g = __gcd(abs(diff.x), abs(diff.y));
      Pt diff2 = diff / g;
      ans += abs(diff.x) / abs(diff2.x);
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<Pt> pts(n+1);
  for (int i = 0; i < n; i++) cin >> pts[i];
  pts[n] = pts[0];
  // Pick theorem: area = interior + boundary / 2 - 1
  ll a2 = area2(pts), boundary = pts_on_boundary(pts);
  ll interior = (a2 + 2 - boundary) / 2;
  cout << interior << ' ' << boundary << '\n';
}
