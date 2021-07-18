class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
      for(int i = 0 ; i < (int)nums.size() ; ++i) {
        while(nums[i] <= (int)nums.size() && nums[i] >= 1 && nums[nums[i] - 1] != nums[i]) {
          swap(nums[nums[i] - 1], nums[i]);
        }
      }
      for(int i = 0 ; i < (int)nums.size() ; ++i) if(nums[i] != i + 1) return i + 1;
      return nums.size() + 1;
    }
};
