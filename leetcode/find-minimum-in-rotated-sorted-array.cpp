class Solution {
private:
    int find(int l, int r, vector<int>& v) {
      if(l == r) return v[l];
      int mid = l + (r - l) / 2, ans = min(v[l], v[mid + 1]);
      if(v[l] > v[mid]) ans = min(ans, find(l, mid, v));
      else ans = min(ans, find(mid + 1, r, v));
      return ans;
    }
public:
    int findMin(vector<int>& nums) {
      return find(0, (int)nums.size() - 1, nums);       
    }
};
