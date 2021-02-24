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
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
      ListNode *now = head, *prev = nullptr, *start, *last, *tmp;
      bool first = true;

      while(1) {
        int cnt = 0;
        start = now;
        while(now && cnt < k) now = now->next, cnt++;
        if(cnt < k) break;
        last = start, now = start->next;
        while(--cnt) {
          tmp = now->next; now->next = last;
          last = now; now = tmp;
        }
        if(prev) prev->next = last;
        start->next = now;
        prev = start;
        if(first) {
          head = last;
          first = 0;
        }
      }
      return head;
    }
};
