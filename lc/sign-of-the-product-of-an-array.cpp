class Solution {
public:
    int arraySign(vector<int>& nums) {
        int pos = 0, neg = 0, zero = 0;
        for(auto num : nums) {
          if(num > 0) pos++;
          else if(num == 0) zero++;
          else neg++;
        }
        if(zero > 0) return 0;
        else return neg % 2 ? -1 : 1;
    }
};
