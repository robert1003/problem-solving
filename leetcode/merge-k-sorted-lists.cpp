/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
private:
    void printList(ListNode* list) {
      while(list) cout << list->val << ',', list=list->next;
      cout << '\n';
    }
    ListNode* merge(ListNode* l1, ListNode* l2) {
      ListNode *head = new ListNode(0), *now = head;
      while(l1 && l2) {
        if(l1->val < l2->val) now->next = l1, now = l1, l1 = l1->next;
        else now->next = l2, now = l2, l2 = l2->next;
      }
      while(l1) now->next = l1, now = l1, l1 = l1->next;
      while(l2) now->next = l2, now = l2, l2 = l2->next;
      ListNode* oriHead = head->next;
      delete head;
      return oriHead;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
      vector<ListNode*> tmp;
      while(lists.size() > 1) {
        tmp.clear();
        for(int i = 0 ; i + 1 < (int)lists.size() ; i += 2) {
          printList(lists[i]);
          printList(lists[i + 1]);
          tmp.push_back(merge(lists[i], lists[i + 1]));
          printList(tmp.back());
          cout << '\n';
        }
        if(lists.size() % 2) tmp.push_back(lists.back());
        swap(lists, tmp);
      }
      if(!lists.empty()) return lists[0];
      return {};
    }
};
