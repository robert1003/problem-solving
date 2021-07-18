class MKAverage {
private:
    static const int N = (int)1e5;
    struct BIT {
        long long n, b[N + 5];
      
        void init(int _n) {
          n = _n;
          fill(b, b + n + 1, 0);
        }
        inline int lowbit(int x) { return x & (-x); }
        void add(int x, int val) {
          for(int i = x ; i <= n ; i += lowbit(i)) {
            b[i] += val;
          }
        }
        long long sum(int x) {
          long long ans = 0;
          for(int i = x ; i > 0 ; i -= lowbit(i)) {
            ans += b[i];
          }
          return ans;
        }
    } bit[2];
    queue<int> q;
    int m, k;

    long long bs(int l, int r, int k) {
      while(l < r) {
        long long mid = l + (r - l) / 2, sum = bit[0].sum(mid);
        if(sum < k) l = mid + 1;
        else r = mid;
      }
      if(bit[0].sum(l) == k) return bit[1].sum(l);
      return bit[1].sum(l - 1) + (long long)l * (k - bit[0].sum(l - 1));
    }
public:
    MKAverage(int m, int k) {
      this->m = m;
      this->k = k;
      bit[0].init(N); bit[1].init(N);
    }
    
    void addElement(int num) {
      bit[0].add(num, 1), bit[1].add(num, num);
      q.push(num);
      if(q.size() > m) {
        bit[0].add(q.front(), -1);
        bit[1].add(q.front(), -q.front());
        q.pop();
      }
    }

    int calculateMKAverage() {
      if(q.size() < m) return -1;
      long long pre = bs(1, N, k), post = bs(1, N, m - k), all = bit[1].sum(N);
      return (all - pre - (all - post)) / (m - k * 2);
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */
