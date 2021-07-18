class Solution {
public:
    int candy(vector<int>& ratings) {
      int n = (int)ratings.size();
      vector<int> deg(n, 0);
      for(int i = 0 ; i < n - 1 ; ++i) {
        if(ratings[i] > ratings[i + 1]) deg[i]++;
        else if(ratings[i] < ratings[i + 1]) deg[i + 1]++;
      }
      int ans = 0;
      queue<array<int, 2> > q;
      for(int i = 0 ; i < n ; ++i) if(deg[i] == 0) q.push({i, 1});
      while(!q.empty()) {
        auto [idx, val] = q.front(); q.pop();
        ans += val;
        if(idx > 0 && ratings[idx - 1] > ratings[idx]) {
          deg[idx - 1]--;
          if(deg[idx - 1] == 0) q.push({idx - 1, val + 1});
        }
        if(idx < n - 1 && ratings[idx + 1] > ratings[idx]) {
          deg[idx + 1]--;
          if(deg[idx + 1] == 0) q.push({idx + 1, val + 1});
        }
      }
      return ans;
    }
};
