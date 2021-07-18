class Solution {
private:
    bool pts_on_line(vector<int>& p1, vector<int>& p2, vector<int>& p3) {
      return (p1[0] - p2[0]) * (p1[1] - p3[1]) == (p1[0] - p3[0]) * (p1[1] - p2[1]);
    }
public:
    int maxPoints(vector<vector<int>>& points) {
      int n = (int)points.size(), ans = 1;
      for(int i = 0 ; i < n ; ++i) {
        for(int j = i + 1 ; j < n ; ++j) {
          int cnt = 0;
          for(int k = 0 ; k < n ; ++k) {
            if(k == i || k == j || pts_on_line(points[k], points[i], points[j])) cnt++;
          }
          ans = max(ans, cnt);
        }
      }
      return ans;
    }
};
