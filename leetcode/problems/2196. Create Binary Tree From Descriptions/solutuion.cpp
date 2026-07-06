#include <bits/stdc++.h>
using namespace std;

//  Definition for a binary tree node.
struct TreeNode
{
    int       val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {};
};

class Solution
{
  public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions)
    {
        unordered_map<int, TreeNode*> nodes;
        unordered_set<int>            children;

        for (const auto& d : descriptions)
        {
            int  parentVal = d[0];
            int  childVal  = d[1];
            bool isLeft    = d[2] == 1;

            // 1. Create parent node if it doesn't exist yet
            if (nodes.find(parentVal) == nodes.end())
            {
                nodes[parentVal] = new TreeNode(parentVal);
            }

            // 2. Create child node if it doesn't exist yet
            if (nodes.find(childVal) == nodes.end())
            {
                nodes[childVal] = new TreeNode(childVal);
            }

            // 3. Connect them
            if (isLeft)
            {
                nodes[parentVal]->left = nodes[childVal];
            }
            else
            {
                nodes[parentVal]->right = nodes[childVal];
            }

            // 4. Mark this node as a child
            children.insert(childVal);
        }

        // 5. Find the root (the only node in 'nodes' that is NOT in 'children')
        for (const auto& pair : nodes)
        {
            if (children.find(pair.first) == children.end())
            {
                return pair.second; // This is the root
            }
        }

        return nullptr;
    }
};
void displayBinaryTreeHorizontal(const TreeNode* root, int depth = 0,
                                 const std::string& prefix = "")
{
    if (!root)
        return;

    // Print right subtree first
    displayBinaryTreeHorizontal(root->right, depth + 1, "/--- ");

    // Print current node
    std::cout << std::string(depth * 4, ' ') << prefix << root->val << '\n';

    // Print left subtree
    displayBinaryTreeHorizontal(root->left, depth + 1, "\\--- ");
}

int main()
{
    vector<vector<int>> data1 = {{20, 15, 1}, {20, 17, 0}, {50, 20, 1}, {50, 80, 0}, {80, 19, 1}};

    vector<vector<int>> data2 = {{1, 2, 1}, {2, 3, 0}, {3, 4, 1}};

    Solution s;

    TreeNode* ans = s.createBinaryTree(data1);

    // TreeNode* t = new TreeNode;
    // t->val      = 10;

    // t->left         = new TreeNode(20);
    // t->right        = new TreeNode(30);
    // t->left->left   = new TreeNode(40);
    // t->left->right  = new TreeNode(45);
    // t->right->left  = new TreeNode(53);
    // t->right->right = new TreeNode(50);

    displayBinaryTreeHorizontal(ans);

    return 0;
}