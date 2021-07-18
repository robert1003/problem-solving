class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
      int n = dungeon.size(), m = dungeon[0].size();
      vector<vector<int> > dp(n + 1, vector<int>(m + 1, (int)-1e9));

      dp[n][m] = dungeon[n - 1][m - 1];
      for(int i = n ; i >= 1 ; --i) {
        for(int j = m ; j >= 1 ; --j) {
          if(i == n && j == m) continue;
          if(i < n) dp[i][j] = max(dp[i][j], min(dp[i + 1][j] + dungeon[i - 1][j - 1], dungeon[i - 1][j - 1]));
          if(j < m) dp[i][j] = max(dp[i][j], min(dp[i][j + 1] + dungeon[i - 1][j - 1], dungeon[i - 1][j - 1]));
        }
      }
      return max(1, -dp[1][1] + 1);
    }
};
