class Solution {
private:
    bool match(char c1, char c2) { return (c1 == '(') && (c2 == ')'); }
public:
    int longestValidParentheses(string s) {
      stack<int> stk;
      stk.push(-1); 
      int ans = 0;
      for(int i = 0 ; i < (int)s.size() ; ++i) {
        if(stk.top() != -1 && match(s[stk.top()], s[i])) {
          stk.pop();
          ans = max(ans, i - stk.top());
        }
        else stk.push(i);
      }
      return ans;
    }
};
