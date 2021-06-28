class Solution {
public:
    long long wonderfulSubstrings(string word) {
        int n = (int)word.size();
        vector<int> cnt(1 << 10, 0);
        long long ans = 0, cur = 0;
        cnt[0] = 1; // empty string
        for(int i = 1; i <= n ; ++i) {
            // update prefix 1 ~ i
            cur ^= (1 << (word[i - 1] - 'a'));
            // find prefixes before i - 1 that matches cur (xor = 0)
            ans += cnt[cur];
            // find prefixes before i - 1 that matches cur (xor with only one bit on)
            for(int j = 1; j < (1 << 10); j <<= 1) {
                ans += cnt[cur ^ j];
            }
            cnt[cur]++;
        }
        return ans;
    }
};
