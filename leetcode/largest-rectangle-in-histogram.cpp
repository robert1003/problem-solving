class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
      vector<array<int, 2> > stk;
      int ans = 0;
      for(int i = 0 ; i < (int)heights.size() ; ++i) {
        int idx = i;
        while(!stk.empty() && heights[i] < stk.back()[0]) {
          ans = max(ans, stk.back()[0] * (i - stk.back()[1]));
          idx = stk.back()[1];
          stk.pop_back();
        }
        stk.push_back({heights[i], idx});
      }
      cout << "ans: " << ans << '\n';
      while(!stk.empty()) {
        cout << stk.back()[0] << '\n';
        ans = max(ans, stk.back()[0] * ((int)heights.size() - stk.back()[1]));
        stk.pop_back();
      }
      return ans;
    }
};
