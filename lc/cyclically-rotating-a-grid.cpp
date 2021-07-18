class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size(), tot = min(n / 2, m / 2);
        for (int t = 0; t < tot; t++) {
            // calculate current width and height, and steps needed to rotate
            int _n = (n - t * 2), _m = (m - t * 2), len = _n * 2 + _m * 2 - 4;
            int _k = k % len;
            
            for (int step = 0; step < _k; step++) {
                // top row
                for (int i = t, j = t; j < m - t - 1; j++) {
                    swap(grid[i][j], grid[i][j + 1]);
                }
                // right col
                for (int i = t, j = m - t - 1; i < n - t - 1; i++) {
                    swap(grid[i][j], grid[i + 1][j]);
                }
                // bottom row
                for (int i = n - t - 1, j = m - t - 1; j >= t + 1; j--) {
                    swap(grid[i][j], grid[i][j - 1]);
                }
                // left col
                for (int i = n - t - 1, j = t; i > t + 1; i--) {
                    swap(grid[i][j], grid[i - 1][j]);
                }
            }
        }
        return grid;
    }
};

