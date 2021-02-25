class Solution {
private:
    void reverse(TreeNode* st, TreeNode* ed) {
      if(st == ed) return;
      TreeNode *cur = st, *nxt = st->right;
      while(cur != ed) {
        TreeNode *tmp = nxt->right;
        nxt->right = cur;
        cur = nxt;
        nxt = tmp;
      }
    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
      vector<int> ans;
      TreeNode *tmp = new TreeNode(0); tmp->left = root;
      TreeNode *cur = tmp;
      while(cur) {
        if(cur->left) {
          TreeNode *p = cur->left;
          while(p->right && p->right != cur) p = p->right;
          if(!p->right) {
            p->right = cur;
            cur = cur->left;
            continue;
          }
          else {
            reverse(cur->left, p);
            TreeNode *dump = p;
            while(1) {
              cerr << dump->val << '\n';
              ans.push_back(dump->val);
              if(dump == cur->left) break;
              dump = dump->right;
            }
            reverse(p, cur->left);
            p->right = nullptr;
          }
        }
        cur = cur->right;
      }
      return ans;
    }
};


