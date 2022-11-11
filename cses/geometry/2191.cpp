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

  Pt operator+(const Pt& p) {
    return Pt(x+p.x, y+p.y);
  }
  Pt operator-(const Pt& p) {
    return Pt(x-p.x, y-p.y);
  }
  ll operator^(const Pt& p) {
    return x*p.y - y*p.x;
  }
  ll operator*(const Pt& p) {
    return x*p.x + y*p.y;
  }
};

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; cin >> n;
  vector<Pt> pts(n+1);
  for (int i = 0; i < n; i++) cin >> pts[i];
  pts[n] = pts[0];

  ll area = 0;
  for (int i = 0; i < n; i++) area += pts[i] ^ pts[i + 1];
  cout << abs(area) << '\n';
}
