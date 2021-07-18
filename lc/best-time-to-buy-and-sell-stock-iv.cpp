class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
      int n = prices.size();
      vector<vector<int> > dp(n + 1, vector<int>(k + 1, 0));

      int ans = 0;
      for(int j = 1 ; j <= k ; ++j) {
        int bst = -1000000; // inf
        for(int i = 1 ; i <= n ; ++i) {
          dp[i][j] = max(dp[i - 1][j], bst + prices[i - 1]);
          bst = max(bst, dp[i][j - 1] - prices[i - 1]);
          ans = max(ans, dp[i][j]);
        }
      }

      return ans;
    }
};
