class Solution {
private:
    static const int maxN = 50, maxM = 100;
    static const int mod = (int)1e9 + 7;
    int dp[maxN + 1][maxN + 1][maxM + 1], pmod[maxM + 5][maxN + 5];

    int powmod(int a, int b) {
      if(!b) return 1;
      if(b == 1) return a;
      int ans = powmod(a, b / 2);
      ans = (long long)ans * ans % mod;
      if(b & 1) ans = (long long)ans * a % mod;
      return ans;
    }
public:
    int numOfArrays(int n, int m, int k) {
      for(int i = 0 ; i < maxM + 5; ++i) {
        pmod[i][0] = 1;
        for(int j = 1 ; j < maxN + 5; ++j) pmod[i][j] = (long long)pmod[i][j - 1] * i % mod;
      }

      for(int j = 1 ; j <= m ; ++j) dp[1][1][j] = 1;

      for(int t = 2 ; t <= k ; ++t) {
        for(int i = 2 ; i <= n ; ++i) {
          for(int j = 2 ; j <= m ; ++j) {
            dp[t][i][j] = dp[t][i][j - 1];
            for(int p = 0 ; p < i ; ++p) {
              dp[t][i][j] = ((long long)dp[t][i][j] + (long long)dp[t - 1][p][j - 1] * pmod[j - 1][i - p - 1]) % mod;
            }
          }
        }
      }

      int ans = 0;
      for(int i = 1 ; i <= n ; ++i) {
        for(int j = 1 ; j <= m ; ++j) {
          ans = ((long long)ans + (long long)dp[k][i][j] * pmod[j][n - i]) % mod;
        }
      }
      return ans;
    }
};
