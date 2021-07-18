class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
      int n = (int)s.size(), m = (int)words[0].size(), uniq = 0;
      unordered_map<string, int> table;
      for(int i = 0 ; i < (int)words.size() ; ++i) {
        if(table.count(words[i]) == 0) table[words[i]] = uniq++;
      }
      vector<int> goal(uniq + 1, 0);
      for(int i = 0 ; i < (int)words.size() ; ++i) goal[table[words[i]]]++;
      set<int> ans;

      for(int i = 0 ; i < m ; ++i) {
        vector<int> in(uniq + 1, 0);
        deque<int> dq;
        int cnt = uniq;
        for(int j = i ; j + m <= n ; j += m) {
          string sub = s.substr(j, m);
          auto it = table.find(sub);
          int idx = (it != table.end() ? it->second : uniq);
          if(in[idx] == goal[idx]) cnt++;
          in[idx]++;
          if(in[idx] == goal[idx]) cnt--;
          dq.push_back(idx);
          
          while(dq.size() > words.size()) {
            idx = dq.front(); dq.pop_front();
            if(in[idx] == goal[idx]) cnt++;
            in[idx]--;
            if(in[idx] == goal[idx]) cnt--;
          }
          if(cnt == 0) ans.insert(j - m * (words.size() - 1));
        }
      }

      return vector<int>(ans.begin(), ans.end());
    }
};
