class Solution {
private:
    static const int M = (int)1e9 + 7;
    static const int N = (int)1e5 + 5;
    // fac[i] = i! % M, rfac[i] = (1 / i!) % M
    long long fac[N], rfac[N];
    vector<int> G[N];
    
    long long powmod(long long a, long long b) {
        if(!b) return 1;
        long long ans = powmod(a, b / 2);
        ans = ans * ans % M;
        if(b & 1) ans = ans * a % M;
        return ans;
    }
    void init() {
        fac[0] = 1;
        for(int i = 1 ; i < N ; ++i) fac[i] = fac[i - 1] * i % M;
        rfac[N - 1] = powmod(fac[N - 1], M - 2);
        for(int i = N - 2 ; i >= 0 ; --i) rfac[i] = rfac[i + 1] * (i + 1) % M;
    }
    pair<long long, int> dfs(int u) {
        int sz = 0;
        long long cnt = 1;
        for(auto v : G[u]) {
            auto p = dfs(v);
            sz += p.second;
            cnt = cnt * rfac[p.second] % M;
            cnt = cnt * p.first % M;
        }
        cnt = cnt * fac[sz] % M;
        return {cnt, sz+1};
    }
public:
    int waysToBuildRooms(vector<int>& prevRoom) {
        init(); int n = prevRoom.size();
        for(int i = 0 ; i < n ; ++i) {
            if(prevRoom[i] == -1) continue;
            G[prevRoom[i]].push_back(i);
        }
        return dfs(0).first;
    }
};
