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

  Pt operator-(const Pt& p) const {
    return Pt(x-p.x, y-p.y);
  }
  ll operator*(const Pt& p) const {
    return x*p.x + y*p.y;
  }
  bool operator==(const Pt& p) const {
    return x == p.x && y == p.y;
  }
  bool operator<(const Pt& p) const {
    return (x < p.x) || (x == p.x && y < p.y);
  }
};

ll norm2(const Pt&& p) {
  return p*p;
}


int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<Pt> pts(n);
  for (int i = 0; i < n; i++) cin >> pts[i];
  sort(pts.begin(), pts.end());

  ll ans = norm2(pts[0]-pts[1]);
  auto cmp = [](Pt p1, Pt p2) { return p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x); };
  set<Pt, decltype(cmp)> candidate(cmp);
  for (int i = 0, j = 0; i < n; i++) {
    if (i == 0) {
      candidate.insert(pts[i]);
      continue;
    }

    while (j < i && pts[i].x - pts[j].x >= ans) {
      candidate.erase(pts[j]);
      j++;
    }

    auto it_start = candidate.lower_bound(Pt(0, pts[i].y - (ll)sqrt(ans)));
    auto it_stop = candidate.upper_bound(Pt((ll)1e10, pts[i].y + (ll)sqrt(ans)));
    while (it_start != it_stop) {
      ans = min(ans, norm2(pts[i] - (*it_start)));
      it_start = next(it_start);
    }

    candidate.insert(pts[i]);
  }

  cout << ans << '\n';
}
