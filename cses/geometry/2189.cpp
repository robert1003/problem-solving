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

  Pt operator-(const Pt& p) {
    return Pt(x - p.x, y - p.y);
  }
  ll operator^(const Pt& p) {
    return x * p.y - y * p.x;
  }
};

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  ll t; cin >> t;
  while (t--) {
    Pt p1, p2, p3;
    cin >> p1 >> p2 >> p3;
    ll cross = (p3 - p1) ^ (p3 - p2);
    if (cross < 0) cout << "RIGHT\n";
    else if (cross == 0) cout << "TOUCH\n";
    else cout << "LEFT\n";
  }
}
