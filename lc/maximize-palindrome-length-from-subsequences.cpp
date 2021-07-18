class Solution {
private:
    void calcDP(vector<vector<int> >& dp, string& s) {
      int n = (int)s.size();
      for(int i = 0 ; i < n ; ++i) {
        dp[i][i] = 1;
        if(i < n - 1) dp[i][i + 1] = (s[i] == s[i + 1] ? 2 : 1);
      }
      for(int k = 3 ; k <= n ; ++k) {
        for(int i = 0 ; i + k - 1 < n ; ++i) {
          int j = i + k - 1;
          dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
          if(s[i] == s[j]) dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + 2);
        }
      }
    }
public:
    int longestPalindrome(string word1, string word2) {
      int n = word1.size(), m = word2.size();
      vector<vector<vector<int> > > dp(4, vector<vector<int> >(n + 1, vector<int>(m + 1, 0)));
      vector<vector<int> > dp1(n + 1, vector<int>(n + 1, 0));
      vector<vector<int> > dp2(m + 1, vector<int>(m + 1, 0));
      calcDP(dp1, word1);
      for(int i = n - 1 ; i >= 0 ; --i) dp[1][i][0] = dp1[i][n - 1];
      calcDP(dp2, word2);
      for(int j = 1 ; j <= m ; ++j) dp[2][n][j] = dp2[0][j - 1];
      for(int i = n - 1 ; i >= 0 ; --i) {
        for(int j = 1 ; j <= m ; ++j) {
          for(int k = 1 ; k < 4 ; ++k)
            dp[k][i][j] = max(dp[k][i + 1][j], dp[k][i][j - 1]);
          if(word1[i] == word2[j - 1]) {
            dp[3][i][j] = max(dp[3][i][j], dp[1][i + 1][j - 1] + 2);
            dp[3][i][j] = max(dp[3][i][j], dp[2][i + 1][j - 1] + 2);
            dp[3][i][j] = max(dp[3][i][j], dp[3][i + 1][j - 1] + 2);
          }
        }
      }
      /*
      for(int i = 0 ; i <= n ; ++i) {
        for(int j = 0 ; j <= m ; ++j) {
          cout << "dp[" << i << "][" << j << "]=" << dp[i][j] << ' ';
        }
        cout << '\n';
      }
      */
      return dp[3][0][m];
    }
};
