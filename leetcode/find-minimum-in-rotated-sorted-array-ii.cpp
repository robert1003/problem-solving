class Solution {
public:
    int findMin(vector<int>& nums) {
      int mn = (int)1e9;
      for(auto num : nums) mn = min(mn, num);
      return mn;
    }
};
