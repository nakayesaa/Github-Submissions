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
    ListNode* mergeKLists(vector<ListNode*>& lists){
        std::vector<int> newVector;
        for(size_t i = 0; i<lists.size();i++){
            ListNode* current = lists[i];
            while(current != nullptr){
                newVector.push_back(current->val);
                current = current->next;
            }
        }

        std::sort(newVector.begin(), newVector.end());
        ListNode result;
        ListNode* tail = &result;

        for(int x : newVector){
            tail->next = new ListNode(x);
            tail = tail->next;
        }

        return result.next;
    }
};
