class Solution {
private:
    static const int maxN = (int)1e5 + 5;
    static const int inf = (int)1e9;
    static const int maxNum = 50 + 1;
    vector<int> G[maxN];
    int gcd[maxNum][maxNum], ans[maxN], num[maxN];
    map<int, set<array<int, 2> > > cnt;

    void dfs(int u, int d, int p) {
      int best_dep = -1, best_idx = -1;
      for(int i = 1 ; i < maxNum ; ++i) if(gcd[num[u]][i] == 1) {
        if(!cnt[i].empty()) {
          auto [dep, idx] = (*cnt[i].rbegin());
          if(best_dep < dep) best_dep = dep, best_idx = idx;
        }
      }
      ans[u] = best_idx;
      cnt[num[u]].insert({d, u});
      for(auto v : G[u]) if(v != p) dfs(v, d + 1, u);
      cnt[num[u]].erase({d, u});
    }
    int __gcd(int a, int b) { return !b ? a : __gcd(b, a % b); }
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
      for(int i = 0 ; i < nums.size() ; ++i) num[i] = nums[i];
      for(auto &e : edges) {
        G[e[0]].push_back(e[1]);
        G[e[1]].push_back(e[0]);
      }
      for(int i = 1 ; i < maxNum ; ++i) {
        for(int j = i ; j < maxNum ; ++j) gcd[i][j] = gcd[j][i] = __gcd(i, j);
      }
      dfs(0, 0, 0);
      return vector<int>(ans, ans + nums.size());
    }
};
