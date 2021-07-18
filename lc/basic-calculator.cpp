class Solution {
public:
    long long calculate(string s) {
      s.push_back(' ');
      vector<long long> stk_num, stk_op;
      long long cur_op = -1, cur_num = -1;
      for(auto c : s) {
        if(isdigit(c)) {
          if(cur_num == -1) cur_num = 0;
          cur_num = cur_num * 10 + c - '0';
        }
        else {
          if(cur_num != -1) {
            //cout << cur_num << ' ' << cur_op << '\n';
            stk_num.push_back(cur_num), cur_num = -1;
            if(cur_op != -1) {
              long long b = stk_num.back(); stk_num.pop_back();
              long long a = 0;
              if(!stk_num.empty()) a = stk_num.back(), stk_num.pop_back();
              //cout << "a:b " << a << (cur_op == 0 ? '+' : '-') << b << '\n';
              stk_num.push_back(cur_op == 0 ? a + b : a - b);
              cur_op = -1;
            }
          }
          if(c == '+') cur_op = 0;
          else if(c == '-') cur_op = 1;
          else if(c == '(') {
            if(cur_op != -1) stk_op.push_back(cur_op), cur_op = -1;
          }
          else if(c == ')') {
            if(!stk_op.empty()) {
              long long b = stk_num.back(); stk_num.pop_back();
              long long a = 0;
              if(!stk_num.empty()) a = stk_num.back(), stk_num.pop_back();
                //cout << " a:b " << a << (stk_op.back() == 0 ? '+' : '-') << b << '\n';
              stk_num.push_back(stk_op.back() == 0 ? a + b : a - b);
              stk_op.pop_back();
            }
          }
        }
      }
      return stk_num.back();
    }
};
