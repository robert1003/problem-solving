class Solution {
public:
    int numDistinct(string s, string t) {
      int n = (int)s.size(), m = (int)t.size();
      vector<vector<long long> > dp(n + 1, vector<long long>(m + 1, 0));
      dp[0][0] = 1;
      for(int i = 1 ; i <= n ; ++i) {
        dp[i][0] = 1;
        for(int j = 1 ; j <= m ; ++j) {
          dp[i][j] = dp[i - 1][j];
          if(s[i - 1] == t[j - 1]) dp[i][j] += dp[i - 1][j - 1];
        }
      }
      return dp[n][m];
    }
};
