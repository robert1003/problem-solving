class Solution {
private:
    int maxRec(vector<int>& h) {
      vector<array<int, 2> > stk;
      int ans = 0;
      for(int i = 0 ; i < (int)h.size() ; ++i) {
        int idx = i;
        while(!stk.empty() && h[i] < stk.back()[0]) {
          ans = max(ans, (i - stk.back()[1]) * stk.back()[0]);
          idx = stk.back()[1];
          stk.pop_back();
        }
        stk.push_back({h[i], idx});
      }
      while(!stk.empty()) {
        ans = max(ans, ((int)h.size() - stk.back()[1]) * stk.back()[0]);
        stk.pop_back();
      }
      return ans;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
      if(matrix.empty() || matrix[0].empty()) return 0;
      int n = matrix.size(), m = matrix[0].size(), ans = 0;
      vector<int> h(m, 0);
      for(int i = 0 ; i < n ; ++i) {
        for(int j = 0 ; j < m ; ++j) {
          if(matrix[i][j] == '0') h[j] = 0;
          else h[j]++;
        }
        cout << "h: ";
        for(auto hh : h) cout << hh << ' ';
        cout << '\n';
        cout << "maxRec: " << maxRec(h) << '\n';
        ans = max(ans, maxRec(h));
      }
      return ans;
    }
};
