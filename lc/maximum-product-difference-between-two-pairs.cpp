// time complexity: O(N)
class Solution {
public:
    int maxProductDifference(vector<int>& nums) {
        int mx = -1, mx2 = -1, mn = 10001, mn2 = 10001;
        for(auto n : nums) {
            if (n > mx) mx2 = mx, mx = n;
            else if (n > mx2) mx2 = n;

            if (n < mn) mn2 = mn, mn = n;
            else if (n < mn2) mn2 = n;
        }
        return mx2 * mx - mn2 * mn;
    }
};
