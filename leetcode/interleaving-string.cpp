class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
      if(s3.size() != s1.size() + s2.size()) return false;
      int n = s1.size(), m = s2.size();
      vector<vector<int> > dp(n + 1, vector<int>(m + 1, 0));
      dp[0][0] = 1;
      for(int i = 0 ; i <= n ; ++i) {
        for(int j = 0 ; j <= m ; ++j) {
          if(i == 0 && j == 0) continue;
          if(i > 0) dp[i][j] |= (s1[i - 1] == s3[i + j - 1] && dp[i - 1][j]);
          if(j > 0) dp[i][j] |= (s2[j - 1] == s3[i + j - 1] && dp[i][j - 1]);
        }
      }
      return dp[n][m];
    }
};
