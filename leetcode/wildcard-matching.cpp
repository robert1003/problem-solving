class Solution {
public:
    bool isMatch(string s, string p) {
      int n = (int)s.size(), m = (int)p.size();
      vector<vector<int> > dp(n + 1, vector<int>(m + 1, 0));

      dp[n][m] = 1;
      for(int i = m - 1 ; i >= 0 && p[i] == '*' ; --i) dp[n][i] = 1;
      //if(p[m - 1] == '?' || p[m - 1] == '*') dp[n - 1][m - 1] = 1;
      //else if(s[n - 1] == p[m - 1]) dp[n - 1][m - 1] = 1;

      for(int j = m - 1 ; j >= 0 ; --j) {
        int suffix = dp[n][j + 1];
        for(int i = n - 1 ; i >= 0 ; --i) {
          suffix |= dp[i][j + 1];

          if(p[j] == '?' || (islower(p[j]) && p[j] == s[i])) {
            dp[i][j] |= dp[i + 1][j + 1];
          }
          else if(p[j] == '*') dp[i][j] |= suffix;
        }
      }

      return dp[0][0];
    }
};
