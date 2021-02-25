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
public:
    vector<int> inorderTraversal(TreeNode* root) {
      vector<int> ans;
      TreeNode* cur = root;
      while(cur) {
        if(cur->left) {
          TreeNode* p = cur->left;
          while(p->right && p->right != cur) p = p->right;
          if(!p->right) {
            p->right = cur;
            cur = cur->left;
            continue;
          }
          else p->right = nullptr;
        }
        ans.push_back(cur->val);
        cur = cur->right;
      }
      return ans;
    }
};
