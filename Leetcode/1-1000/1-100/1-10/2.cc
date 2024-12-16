#include "../../../dependencies.h"

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
      ListNode *result = new ListNode();
      ListNode *resultPtr = result;
        int tens = 0, flag = 0;
        while (l1 || l2)
        {
            if (l1 && l2) {
                result->val = (l1->val + l2->val + tens) % 10;
                tens = (l1->val + l2->val + tens) / 10;
                l1 = l1->next;
                l2 = l2->next;
                if (l1 || l2) {
                    result->next = new ListNode();
                    result = result->next;
                }
            }
            else if (l1) {
                result->val = (l1->val + tens) % 10;
                tens = (l1->val + tens) / 10;
                l1 = l1->next;
                if (l1) {
                    result->next = new ListNode();
                    result = result->next;
                }
            } else {
                result->val = (l2->val + tens) % 10;
                tens = (l2->val + tens) / 10;
                l2 = l2->next;
                if (l2) {
                    result->next = new ListNode();
                    result = result->next;
                }
            }
        }
        if (tens) {
            result->next = new ListNode();
            result = result->next;
            result->val = tens;
        }
        return resultPtr;
    }
};

int main() {
  Solution sol;
}