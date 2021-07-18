class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
      unordered_set<int> s;
      for(auto num : nums) s.insert(num);
      int ans = 0;
      for(auto num : nums) if(s.count(num)) {
        int curl = num - 1, curr = num + 1; s.erase(num);
        while(s.count(curl)) { s.erase(curl--); }
        while(s.count(curr)) { s.erase(curr++); }
        ans = max(ans, curr - curl - 1);
      }
      return ans;
    }
};
