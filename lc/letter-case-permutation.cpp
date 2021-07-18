class Solution {
private:
    void dfs(string& S, vector<string>& ans, int i, string& now) {
      if(i == (int)S.size()) {
        ans.push_back(now);
        return;
      }

      if(isalpha(S[i])) {
        now.push_back(tolower(S[i]));
        dfs(S, ans, i + 1, now);
        now.pop_back();

        now.push_back(toupper(S[i]));
        dfs(S, ans, i + 1, now);
        now.pop_back();
      }
      else {
        now.push_back(S[i]);
        dfs(S, ans, i + 1, now);
        now.pop_back();
      }
    }
public:
    vector<string> letterCasePermutation(string S) {
      vector<string> ans;
      string now = "";
      dfs(S, ans, 0, now);
      return ans;
    }
};
