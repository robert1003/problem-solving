class Solution {
public:
    int trap(vector<int>& height) {
      vector<array<int, 2> > stk;
      int ans = 0;
      for(int i = 0 ; i < (int)height.size() ; ++i) {
        int level = 0;
        while(!stk.empty() && height[i] >= stk.back()[0]) {
          ans += (stk.back()[0] - level) * (i - stk.back()[1] - 1);
          level = stk.back()[0];
          stk.pop_back();
        }
        if(!stk.empty()) ans += (height[i] - level) * (i - stk.back()[1] - 1);
        stk.push_back({height[i], i});
      }
      return ans;
    }
};
