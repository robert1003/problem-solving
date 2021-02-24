class Solution {
public:
    int jump(vector<int>& nums) {
      int mx = nums[0], cur = 0, step = 0;
      while(mx < nums.size() - 1) {
        int tmp = mx;
        while(cur <= mx) tmp = max(tmp, cur + nums[cur]), cur++;
        step += 1;
        mx = tmp;
      }
      if(nums.size() == 1) return 0;
      return step + 1;
    }
};
