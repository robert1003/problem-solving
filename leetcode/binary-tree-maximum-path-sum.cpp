/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    int ans = (int)-1e8;
    void update(array<int, 2>& mx, int val) {
      if(val >= mx[0]) { mx[1] = mx[0], mx[0] = val; }
      else if(val >= mx[1]) mx[1] = val;
    }
    int dfs(TreeNode* node) {
      array<int, 2> mx = {0, (int)-1e8};
      if(node->left) update(mx, dfs(node->left));
      if(node->right) update(mx, dfs(node->right));
      ans = max(ans, mx[0] + (mx[1] < 0 ? 0 : mx[1]) + node->val);
      return max(mx[0], mx[1]) + node->val;
    }
public:
    int maxPathSum(TreeNode* root) {
      dfs(root); 
      return ans;
    }
};
