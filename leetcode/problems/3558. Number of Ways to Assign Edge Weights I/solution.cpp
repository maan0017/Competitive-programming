#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;

struct Tree
{
    int   val;
    int   weight;
    Tree* left;
    Tree* right;

    explicit Tree(int val) : val(val), weight(0), left(nullptr), right(nullptr) {}
    // 'explicit' prevents accidental conversions like Tree t = 5;
};

class Solution
{
    int M = 1e9 + 7;

    // Moved inside the class for better encapsulation
    long long power(long long base, long long exponent)
    {
        if (exponent == 0)
            return 1;
        long long half   = power(base, exponent / 2);
        long long result = (half * half) % M;
        if (exponent % 2 == 1)
        {
            result = (result * base) % M;
        }
        return result;
    }

    int getMaxDepth(vector<vector<int>>& adj, int node, int parent)
    {
        int depth = 0;
        for (int ngbr : adj[node])
        {
            if (ngbr == parent)
                continue;
            depth = max(depth, getMaxDepth(adj, ngbr, node) + 1);
        }
        return depth;
    }

  public:
    int assignEdgeWeights(vector<vector<int>>& edges)
    {
        int n = edges.size() + 1; // n-1 edges means n nodes

        // Edge Case: If there is only 1 node, the path length is 0.
        // Sum is 0 (even). Number of ways to get an odd sum is 0.
        if (n == 1)
            return 0;

        // Optimization: Use a 2D vector instead of unordered_map
        vector<vector<int>> adj(n + 1);
        for (auto& edge : edges)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        int maxDept = getMaxDepth(adj, 1, -1);

        // Fix: Use your custom modular exponentiation function!
        return power(2, maxDept - 1);
    }
};
// ----- CONSTRAINTS
// 2 <= n <= 105
// edges.length == n - 1
// edges[i] == [ui, vi]
// 1 <= ui, vi <= n
// edges represents a valid tree.

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    vector<vector<int>> data1     = {{1, 2}};
    int                 expected1 = 1;

    vector<vector<int>> data2     = {{1, 2}, {1, 3}, {3, 4}, {3, 5}};
    int                 expected2 = 2;

    Solution s;
    // call that function here ->
    int output1 = s.assignEdgeWeights(data1);
    int output2 = s.assignEdgeWeights(data2);

    cout << "output 1:" << output1 << endl;
    cout << "output 1:" << output2 << endl;

    return 0;
}
