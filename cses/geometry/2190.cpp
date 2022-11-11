#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Pt {
  ll x, y;

  Pt () {}
  Pt (ll _x, ll _y) : x(_x), y(_y) {}
  Pt (const Pt& _p) : x(_p.x), y(_p.y) {}

  friend istream& operator>>(istream& in, Pt& p) {
    in >> p.x >> p.y;
    return in;
  }
  friend ostream& operator<<(ostream& out, Pt &&p) {
    out << "(" << p.x << "," << p.y << ")";
    return out;
  }

  bool operator==(const Pt& p) const {
    return x == p.x && y == p.y;
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
};

ll sgn(ll x) {
  return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

ll ori(const Pt& o, const Pt& a, const Pt& b) {
  return sgn((a-o)^(b-o));
}

bool intersect(const Pt& p1, const Pt& p2, const Pt& q1, const Pt& q2) {
  // parallel
  if (((p2 - p1) ^ (q2 - q1)) == 0) {
    // endpoint overlap
    if (ori(p1, p2, q1)) return false;

    return ((p1 - q1)*(p2 - q1)) <= 0 || ((p1 - q2)*(p2 - q2)) <= 0 ||
           ((q1 - p1)*(q2 - p1)) <= 0 || ((q1 - p2)*(q2 - p2)) <= 0;
  }

  return (ori(p1, p2, q1)*ori(p1, p2, q2) <= 0) && (ori(q1, q2, p1)*ori(q1, q2, p2) <= 0);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while (t--) {
    Pt p1, p2, q1, q2;
    cin >> p1 >> p2 >> q1 >> q2;
    cout << (intersect(p1, p2, q1, q2) ? "YES\n" : "NO\n");
  }
}
