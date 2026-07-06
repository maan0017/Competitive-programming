#pragma once
#include <iostream>
#include <vector>
using namespace std;

// singly linked list (one-direction)
struct ListNode
{
    int       val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// create singly linked list
ListNode* createList(vector<int> arr)
{
    int n = arr.size();
    if (!n)
        return nullptr;

    ListNode* head = new ListNode();
    ListNode* temp = head;

    for (int i = 0; i < n; i++)
    {
        temp->val = arr[i];
        if (i < n - 1)
        {
            temp->next = new ListNode();
            temp       = temp->next;
        }
    }

    return head;
}

// display singly linked list
void displayList(ListNode* list)
{
    std::cout << "head";
    while (list != nullptr)
    {
        std::cout << " -> " << list->val;
        list = list->next;
    }

    std::cout << std::endl;
}