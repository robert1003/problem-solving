class Solution {
private:
    inline bool match(char c1, char c2) { return c1 == c2 || c2 == '.'; }
    bool dfs(string& s, string& p, int idx_s, int idx_p) {
      if(idx_p == (int)p.size()) return idx_s == (int)s.size();
      if(idx_s == (int)s.size()) {
        bool need = false;
        while(idx_p < (int)p.size()) {
          if(need) {
            if(p[idx_p] != '*') return false;
            else need = false;
          }
          else if(p[idx_p] != '-') need = true;
          idx_p++;
        }

        return need == false;
      }

      bool extra = (idx_p + 1 < (int)p.size() && p[idx_p + 1] == '*');
      if(!extra) {
        if(!match(s[idx_s], p[idx_p])) return false;
        return dfs(s, p, idx_s + 1, idx_p + 1);
      }
      if(dfs(s, p, idx_s, idx_p + 2)) return true;
      for(int i = idx_s ; i < (int)s.size() && match(s[i], p[idx_p]) ; ++i) {
        if(dfs(s, p, i + 1, idx_p + 2)) return true;
      }
      return false;
    }
public:
    bool isMatch(string s, string p) {
      return dfs(s, p, 0, 0); 
    }
};
