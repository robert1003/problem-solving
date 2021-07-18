class Solution {
public:
    static const int M = (int)1e9 + 7;
    using ll = long long;
    
    ll powmod(ll a, ll b) {
        if (!b) return 1;
        ll ans = powmod(a, b / 2);
        ans = ans * ans % M;
        if (b & 1) ans = ans * a % M;
        return ans;
    }
    
    int countGoodNumbers(long long n) {
        return powmod(5, (n + 1) / 2) * powmod(4, n / 2) % M;
    }
};
