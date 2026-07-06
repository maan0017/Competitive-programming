#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../singlyLinkedList.h"

class Solution
{
  public:
    ListNode* deleteMiddle(ListNode* head)
    {
        // Base case: If the list is empty or has only 1 node,
        // the middle node is the only node. Return null to delete it.
        if (head == nullptr || head->next == nullptr)
        {
            return nullptr;
        }

        // Initialize slow at head, and fast two steps ahead
        ListNode* slow = head;
        ListNode* fast = head->next->next;

        // Traverse the list
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // slow is now positioned right before the middle node.
        // We delete the middle node by skipping it.
        ListNode* toDelete = slow->next; // Optional: keep track if you need to free memory manually
        slow->next         = slow->next->next;

        // Optional: delete toDelete; (Good practice in C++ to avoid memory leaks)
        delete toDelete;
        toDelete = nullptr;

        return head;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    vector<int> data1     = {1, 3, 4, 7, 1, 2, 6};
    vector<int> expected1 = {1, 3, 4, 1, 2, 6};
    ListNode*   list1     = createList(data1);

    vector<int> data2     = {1, 2, 3, 4};
    vector<int> expected2 = {1, 2, 4};
    ListNode*   list2     = createList(data2);

    vector<int> data3     = {2, 1};
    vector<int> expected3 = {2};
    ListNode*   list3     = createList(data3);

    Solution s;
    // call that function here ->
    s.deleteMiddle(list1);
    s.deleteMiddle(list2);
    s.deleteMiddle(list3);

    // display answered lists
    displayList(list1);
    displayList(list2);
    displayList(list3);

    return 0;
}