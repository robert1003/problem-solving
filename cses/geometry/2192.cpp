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
    return Pt(x-p.x, y-p.y);
  }
  Pt operator+(const Pt& p) {
    return Pt(x+p.x, y+p.y);
  }
  ll operator^(const Pt& p) {
    return x*p.y - y*p.x;
  }
  ll operator*(const Pt& p) {
    return x*p.x + y*p.y;
  }
};

bool onseg(Pt& o, Pt& a, Pt& b) {
  return (((a-o)^(b-o)) == 0) && (((a-o)*(b-o)) <= 0);
}

ll ori(Pt& o, Pt& a, Pt& b) {
  ll res = (a-o)^(b-o);
  return (res>0)-(res<0);
}

int inPoly(Pt& p, vector<Pt>& v) {
  int n = v.size()-1, cnt = 0;
  for (int i = 0; i < n; i++) {
    if (onseg(p, v[i], v[i+1])) return -1;
    ll k = ori(p, v[i], v[i+1]);
    ll d1 = v[i].y - p.y, d2 = v[i+1].y - p.y;
    if (k > 0 && d1 <= 0 && d2 > 0) cnt++;
    if (k < 0 && d2 <= 0 && d1 > 0) cnt--;
  }
  return cnt != 0;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, m; cin >> n >> m;
  vector<Pt> poly(n+1);
  for (int i = 0; i < n; i++) cin >> poly[i];
  poly[n] = poly[0];

  while (m--) {
    Pt p; cin >> p;
    int res = inPoly(p, poly);
    if (res == -1) cout << "BOUNDARY\n";
    else if (res > 0) cout << "INSIDE\n";
    else cout << "OUTSIDE\n";
  }
}
