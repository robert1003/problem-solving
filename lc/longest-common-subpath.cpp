class Solution {
public:
    using ll = long long;
    class Hash {
    private:
        int maxLen, curLen;
        vector<pair<int, int> > hash_pair;
        vector<vector<ll> > preHash, pow;
    public:
        Hash(vector<pair<int, int> > hash_pair, int maxLen) {
            this->hash_pair = hash_pair;
            this->maxLen = maxLen;

            for (auto [x, M] : hash_pair) {
                vector<ll> _pow(maxLen + 1, 0);
                _pow[0] = 1;
                for (int i = 1; i <= maxLen; i++) {
                    _pow[i] = _pow[i - 1] * x % M;
                }
                pow.push_back(_pow);
            }
        }

        void init(string& s, char base) {
            preHash.clear(); curLen = (int)s.size();
            for (auto [x, M] : hash_pair) {
                vector<ll> _preHash(s.size() + 1, 0);
                _preHash[0] = 0;
                for (int i = 1; i <= curLen; i++) {
                    _preHash[i] = (_preHash[i - 1] * x % M + (s[i - 1] - base + 1)) % M;
                }
                preHash.push_back(_preHash);
            }
        }

        void init(vector<int>& s, int base) {
            preHash.clear(); curLen = (int)s.size();
            for (auto [x, M] : hash_pair) {
                vector<ll> _preHash(s.size() + 1, 0);
                _preHash[0] = 0;
                for (int i = 1; i <= curLen; i++) {
                    _preHash[i] = (_preHash[i - 1] * x % M + (s[i - 1] - base + 1)) % M;
                }
                preHash.push_back(_preHash);
            }
        }

        vector<ll> getHashVal(int idx, int len) {
            vector<ll> res;
            for (int i = 0; i < (int)hash_pair.size(); i++) {
                auto [_, M] = hash_pair[i];
                res.push_back((preHash[i][idx] - preHash[i][idx - len] * pow[i][len] % M + M) % M);
            }
            return res;
        }
    };


    bool test(int len, vector<vector<int>>& paths, vector<Hash>& hashs) {
        return true;
    }

    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
        vector<Hash> hashs; int mn = (int)1e9;
        vector<pair<int, int> > hash_pairs;
        hash_pairs.push_back({31, 998244353});
        hash_pairs.push_back({17, 1000000007});
        for (auto path : paths) {
            Hash hash = new Hash(hash_pairs, 100005);
            hash.init(path, 0);
            hashs.push_back(hash);
            mn = min((int)path.size() + 1, mn);
        }

        int l = 0, r = mn;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            if (test(mid, paths, hashs)) l = mid;
            else r = mid;
        }
        return l;
    }
}

