const int maxN = (int)1e5 + 5;
struct Trie {
    int root, tot = 0;
    int ch[maxN * 20][2], cnt[maxN * 20];
    
    void init() {
        root = tot++;
    }
    int newNode() {
        fill(ch[tot], ch[tot] + 2, 0);
        cnt[tot] = 0;
        return tot++;
    }
    void insert(int x) {
        int cur = root;
        for (int i = 19; i >= 0; i--) {
            int t = (x & (1 << i) ? 1 : 0);
            if (!ch[cur][t]) ch[cur][t] = newNode();
            //cout << "insert " << x << ' ' << i << ' ' << t << ' ' << ch[cur][t] << ' ' << cnt[ch[cur][t]] << '\n';
            cnt[ch[cur][t]]++;
            cur = ch[cur][t];
        }
    }
    void remove(int x) {
        int cur = root;
        for (int i = 19; i >= 0; i--) {
            int t = (x & (1 << i) ? 1 : 0);
            cnt[ch[cur][t]]--;
            cur = ch[cur][t];
        }
    }
    int query(int x) {
        int cur = root, ans = 0;
        for (int i = 19; i >= 0; i--) {
            int t = (x & (1 << i) ? 1 : 0);
            if (cnt[ch[cur][!t]]) ans += (1 << i), cur = ch[cur][!t];
            else cur = ch[cur][t];
            //cout << "query " << x << ' ' << i << ' ' << t << ' ' << cnt[ch[cur][0]] << ' ' << cnt[ch[cur][1]] << '\n';
        }
        return ans;
    }
} trie;

class Solution {
    
    vector<int> G[maxN];
    vector<pair<int, int>> query[maxN];
    vector<int> ans;
    void dfs(int u, int p) {
        trie.insert(u);
        for (auto [idx, x] : query[u]) {
            ans[idx] = trie.query(x);
        }
        for (auto v : G[u]) if (v != p) {
            dfs(v, u);
        }
        trie.remove(u);
    }

public:
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        int root = -1;
        for (int i = 0; i < (int)parents.size(); i++) {
            if (parents[i] != -1) {
                G[parents[i]].push_back(i);
                G[i].push_back(parents[i]);
            } else root = i;
        }
        
        for (int i = 0; i < (int)queries.size(); i++) {
            int u = queries[i][0], x = queries[i][1];
            query[u].push_back({i, x});
        }
        
        ans.resize((int)queries.size(), -1);
        trie.init();
        dfs(root, root);
        
        return ans;
    }
};
