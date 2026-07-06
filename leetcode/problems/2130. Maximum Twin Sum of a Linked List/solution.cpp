#include "singlyLinkedList.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;

class Solution
{
  public:
    int pairSum(ListNode* head)
    {
        // 1. calculate the size of list
        int       n   = 0; // list size
        ListNode* end = head;
        while (end != nullptr)
        {
            n++;
            end = end->next;
        }
        std::cout << "size of list :" << n << std::endl;

        ListNode* half    = head;
        int       halfLen = n / 2;
        while (halfLen > 0)
        {
            half = half->next;
            halfLen--;
        }

        std::stack<int> st;
        while (half != nullptr)
        {
            st.push(half->val);
            half = half->next;
        }

        int maxSum = 0;

        while (!st.empty())
        {
            int sum = head->val + st.top();
            maxSum  = std::max(sum, maxSum);

            // short from both sides
            head = head->next;
            st.pop();
        }

        return maxSum;
    }
};

class Solution2
{
  public:
    int pairSum(ListNode* head)
    {
        // 1. Find the middle of the linked list
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2. Reverse the second half of the linked list in-place
        ListNode* prev = nullptr;
        ListNode* curr = slow;

        while (curr != nullptr)
        {
            ListNode* nextNode = curr->next;
            curr->next         = prev;
            prev               = curr;
            curr               = nextNode;
        }

        // 3. Calculate the maximum twin sum
        int       maxSum     = 0;
        ListNode* firstHalf  = head;
        ListNode* secondHalf = prev; // 'prev' is the new head of the reversed half

        while (secondHalf != nullptr)
        {
            maxSum     = std::max(maxSum, firstHalf->val + secondHalf->val);
            firstHalf  = firstHalf->next;
            secondHalf = secondHalf->next;
        }

        return maxSum;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    vector<int> data1 = {5, 4, 2, 1};
    // int         expected1 = 6;
    ListNode* list1 = createList(data1);
    displayList(list1);

    vector<int> data2 = {4, 2, 2, 3};
    // int         expected2 = 7;
    ListNode* list2 = createList(data2);
    displayList(list2);

    vector<int> data3 = {1, 100000};
    // int         expected3 = 100001;
    ListNode* list3 = createList(data3);
    displayList(list3);

    Solution s;
    // call that function here ->
    int output1 = s.pairSum(list1);
    int output2 = s.pairSum(list2);
    int output3 = s.pairSum(list3);

    std::cout << "output1 :" << output1 << std::endl;
    std::cout << "output2 :" << output2 << std::endl;
    std::cout << "output3 :" << output3 << std::endl;

    return 0;
}