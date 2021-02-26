class Solution {
public:
    bool checkPartitioning(string s) {
      int n = (int)s.size();
      vector<vector<int> > isvalid(n + 1, vector<int>(n + 1, 0));
      for(int i = 1 ; i <= n ; ++i) isvalid[i][i] = 1;
      for(int i = 1 ; i < n ; ++i) isvalid[i][i + 1] = s[i - 1] == s[i];
      for(int k = 3 ; k <= n ; ++k) {
        for(int i = 1 ; i + k - 1 <= n ; ++i) {
          int j = i + k - 1;
          if(s[i - 1] == s[j - 1]) isvalid[i][j] = isvalid[i + 1][j - 1];
        }
      }
      vector<vector<int> > dp(n + 1, vector<int>(4, 0));
      dp[0][0] = 1;
      for(int k = 1 ; k <= 3 ; ++k) {
        for(int i = 1 ; i <= n ; ++i) {
          for(int j = 1 ; j <= i ; ++j) {
            if(isvalid[j][i]) dp[i][k] |= dp[j - 1][k - 1];
          }
        }
      }
      return dp[n][3];
    }
};
