class Solution {
private:
    double crash(array<int, 3>& c1, array<int, 3>& c2) {
      return (double)(c2[1] - c1[1]) / (c1[2] - c2[2]);
    }
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
      int n = (int)cars.size();
      vector<double> ans(n, -1);
      vector<array<int, 3> > stk;
      for(int i = n - 1 ; i >= 0 ; --i) {
        array<int, 3> cur = {i, cars[i][0], cars[i][1]};
        while(!stk.empty() && cur[2] <= stk.back()[2]) {
          if(stk.size() > 1) {
            ans[stk[stk.size() - 1][0]] = crash(stk[stk.size() - 1], stk[stk.size() - 2]);
          }
          stk.pop_back();
        }
        while(stk.size() > 1 && crash(cur, stk[stk.size() - 1]) > crash(stk[stk.size() - 1], stk[stk.size() - 2])) {
          ans[stk[stk.size() - 1][0]] = crash(stk[stk.size() - 1], stk[stk.size() - 2]);
          stk.pop_back();
        }
        stk.push_back(cur);
      }
      while(stk.size() > 1) {
        ans[stk[stk.size() - 1][0]] = crash(stk[stk.size() - 1], stk[stk.size() - 2]);
        stk.pop_back();
      }
      return ans;
    }
};
