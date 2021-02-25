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
    void recoverTree(TreeNode* root) {
      TreeNode *cur = root, *pre = nullptr, *first = nullptr, *second = nullptr;
      while(cur) {
        if(cur->left) {
          TreeNode *p = cur->left;
          while(p->right && p->right != cur) p = p->right;
          if(!p->right) {
            p->right = cur;
            cur = cur->left;
            continue;
          }
          else p->right = nullptr;
        }
        if(pre && pre->val > cur->val) {
          if(!first) first = pre;
          second = cur;
        }
        pre = cur;
        cur = cur->right;
      }
      swap(first->val, second->val);
    }
};
