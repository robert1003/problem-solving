class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        vector<pair<double, int> > time2reach(dist.size(), make_pair(0, 0));
        for (int i = 0; i < dist.size(); i++) {
            time2reach[i] = make_pair((double)dist[i] / speed[i], i);
        }
        sort(time2reach.begin(), time2reach.end());
        int ans = 0;
        for (int i = 0; i < time2reach.size(); i++) {
            if (time2reach[i].first <= i) break;
            ans++;
        }
        return ans;
    }
};
