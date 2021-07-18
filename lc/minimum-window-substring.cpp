class Solution {
private:
    int idx(char c) {
      if(islower(c)) return c - 'a';
      if(isupper(c)) return c - 'A' + 26;
      __builtin_unreachable();
    }
public:
    string minWindow(string s, string t) {
      vector<int> tar(52, 0);
      for(int i = 0 ; i < (int)t.size() ; ++i) tar[idx(t[i])]++;
      int miss = 0;
      for(int i = 0 ; i < 52 ; ++i) if(tar[i]) miss++;

      vector<int> cnt(52, 0);
      int al = 0, ar = 1000000;
      for(int i = 0, l = 0 ; i < (int)s.size() ; ++i) {
        cnt[idx(s[i])]++;
        if(cnt[idx(s[i])] == tar[idx(s[i])] && tar[idx(s[i])]) miss--;
        
        while(l < i && miss == 0) {
          if(cnt[idx(s[l])] == tar[idx(s[l])] && tar[idx(s[l])]) break;
          cnt[idx(s[l])]--;
          l++;
        }

        if(miss == 0 && i - l < ar - al) al = l, ar = i;
      }

      if(ar - al > s.size()) return "";
      return s.substr(al, ar - al + 1);
    }
};
