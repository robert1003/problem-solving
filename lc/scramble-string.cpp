class Solution {
private:
    bool DP(vector<vector<vector<int> > >& dp, string& s1, string& s2, int l, int r, int s) {
      if(dp[l][r][s] >= 0) return dp[l][r][s];
      if(l == r) return dp[l][r][s] = s1[l - 1] == s2[s - 1];
      dp[l][r][s] = 0;
      for(int i = l ; i < r ; ++i) {
        dp[l][r][s] |= (DP(dp, s1, s2, l, i, s) && DP(dp, s1, s2, i + 1, r, s + i - l + 1));
        dp[l][r][s] |= (DP(dp, s1, s2, l, i, s + r - i) && DP(dp, s1, s2, i + 1, r, s));
      }
      return dp[l][r][s];
    }
public:
    bool isScramble(string s1, string s2) {
      int n = (int)s1.size();
      vector<vector<vector<int> > > dp(n + 1, vector<vector<int> >(n + 1, vector<int>(n + 1, -1)));
      return DP(dp, s1, s2, 1, n, 1);
    }
};
