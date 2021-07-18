class Solution {
private:
    bool isDigits(string s) {
      int cnt = 0;
      for(int i = 0 ; i < (int)s.size() ; ++i) {
        if(!isdigit(s[i])) return false;
        cnt++;
      }
      return cnt > 0;
    }
    bool isInteger(string s) {
      int idx = 0;
      if(s[0] == '+' || s[0] == '-') idx++;
      return isDigits(s.substr(idx, s.size() - idx));
    }
    bool isDecimal(string s) {
      int idx = 0, cnt = 0;
      if(s[0] == '+' || s[0] == '-') idx++;
      int dot = -1;
      for(int i = idx ; i < (int)s.size() ; ++i) if(s[i] == '.') {
        if(dot != -1) return false;
        dot = i;
      }
      string p1 = s.substr(idx, dot - idx);
      string p2 = s.substr(dot + 1, s.size() - dot - 1);
      if(p1.empty() && p2.empty()) return false;
      else if(p1.empty()) return isDigits(p2);
      else if(p2.empty()) return isDigits(p1);
      else return isDigits(p1) && isDigits(p2);
    }
    bool isScientificNumber(string s) {
      int idx_E = -1;
      for(int i = 0 ; i < (int)s.size() ; ++i) {
        if(s[i] == 'e' || s[i] == 'E') {
          if(idx_E != -1) return false;
          idx_E = i;
        }
      }
      if(idx_E == -1) return false;
      string p1 = s.substr(0, idx_E);
      string p2 = s.substr(idx_E + 1, s.size() - idx_E - 1);
      return (isInteger(p1) || isDecimal(p1)) && isInteger(p2);
    }
public:
    bool isNumber(string s) {
      if(isInteger(s) || isDecimal(s) || isScientificNumber(s)) return true;
      return false;
    }
};
