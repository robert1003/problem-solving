class Solution {
public:
    string getPermutation(int n, int k) {
      k--;
      vector<int> used(n + 1, 0), fac(n + 1, 0);
      fac[0] = fac[1] = 1;
      for(int i = 2 ; i <= n ; ++i) fac[i] = fac[i - 1] * i;
      string ans = "";
      for(int i = 1 ; i <= n ; ++i) {
        int cnt = 0, idx = 1;
        while(used[idx]) idx++;
        for(int j = idx + 1 ; j <= n ; ++j) if(!used[j]) {
          if(cnt + fac[n - i] <= k) idx = j, cnt += fac[n - i];
        }
        k -= cnt;
        ans.push_back('0' + idx);
        used[idx] = 1;
      }
      return ans;
    }
};
