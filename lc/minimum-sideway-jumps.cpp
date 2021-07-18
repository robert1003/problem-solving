class Solution {
private:
    static const int N = (int)5e5 + 5;
    static const int inf = (int)1e9;
    int dp[N][3];
public:
    int minSideJumps(vector<int>& obstacles) {
        int n = (int)obstacles.size();
        for(int i = 0 ; i < n ; ++i) fill(dp[i], dp[i] + 3, inf);
        dp[0][1] = 0; dp[0][0] = dp[0][2] = 1;
        for(int i = 1 ; i < n ; ++i) {
          for(int j = 0 ; j < 3 ; ++j) {
            if(obstacles[i] - 1 != j) {
              dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            }
          }
          for(int j = 0 ; j < 3 ; ++j) {
            for(int k = 0 ; k < 3 ; ++k) if(j != k) {
              if(obstacles[i] - 1 != j && obstacles[i] - 1 != k) {
                dp[i][j] = min(dp[i][j], dp[i][k] + 1);
              }
            }
          }
        }
        return min(dp[n - 1][0], min(dp[n - 1][1], dp[n - 1][2]));
    }
};
