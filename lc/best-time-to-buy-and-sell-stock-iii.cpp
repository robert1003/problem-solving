class Solution {
public:
    int maxProfit(vector<int>& prices) {
      int n = (int)prices.size(), mn = 1e6, ans = 0;
      vector<int> best(n + 1, 0);
      for(int i = 1 ; i <= n ; ++i) {
        best[i] = max(best[i - 1], prices[i - 1] - mn);
        ans = max(ans, best[i]);
        mn = min(mn, prices[i - 1]);
      }
      vector<int> pre(n + 1, 0);
      for(int i = 1 ; i <= n ; ++i) pre[i] = best[i - 1] - prices[i - 1];
      int mx = -1e6;
      for(int i = 1 ; i <= n ; ++i) {
        ans = max(ans, mx + prices[i - 1]);
        mx = max(mx, pre[i]);
      }
      return ans;
    }
};
