class Solution {
private:
    int solve(vector<int>& v1, vector<int>& v2, int idx) {
      int l = 0, r = min((int)v1.size(), idx), mid, pos, ok;
      while(l + 1 < r) {
        mid = l + (r - l) / 2, pos = idx - (mid + 1) - 1;
        
        if(pos + 1 >= 0 && pos + 1 < (int)v2.size() && v1[mid] > v2[pos + 1]) r = mid;
        else if(pos >= 0 && pos < (int)v2.size() && v1[mid] < v2[pos]) l = mid + 1;
        else l = mid;
      }
      pos = idx - (l + 1) - 1, ok = 1;
      if(l >= r) ok = 0;
      else if(pos + 1 >= 0 && pos + 1 < (int)v2.size() && v1[l] > v2[pos + 1]) ok = 0;
      else if(pos >= 0 && pos < (int)v2.size() && v1[l] < v2[pos]) ok = 0;
      if(ok) return v1[l];

      l = 0, r = min((int)v2.size(), idx), mid, ok = 0;
      while(l + 1 < r) {
        mid = l + (r - l) / 2, pos = idx - (mid + 1) - 1;

        if(pos + 1 >= 0 && pos + 1 < (int)v1.size() && v2[mid] > v1[pos + 1]) r = mid;
        else if(pos >= 0 && pos < (int)v1.size() && v2[mid] < v1[pos]) l = mid + 1;
        else l = mid;
      }
      pos = idx - (l + 1) - 1, ok = 1;
      if(l >= r) ok = 0;
      else if(pos + 1 >= 0 && pos + 1 < (int)v1.size() && v2[l] > v1[pos + 1]) ok = 0;
      else if(pos >= 0 && pos < (int)v1.size() && v2[l] < v1[pos]) ok = 0;
      assert(ok);
      return v2[l];
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
      if(nums1.size() < nums2.size()) swap(nums1, nums2);
      int n = (int)nums1.size(), m = (int)nums2.size(), tot = n + m;
      if(tot % 2) return (double)solve(nums1, nums2, (tot + 1) / 2);
      else {
        int m1 = solve(nums1, nums2, tot / 2); 
        int m2 = solve(nums1, nums2, tot / 2 + 1);
        return (double)(m1 + m2) / 2;
      }
      __builtin_unreachable();
    }
};
