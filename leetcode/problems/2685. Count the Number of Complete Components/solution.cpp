#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class Solution
{
  public:
    int countCompleteComponents(int n, std::vector<std::vector<int>>& edges)
    {
        // assuming edges are sorted according to the edge numbers

        std::vector<std::vector<int>> adj(n);
        // seperate component groups
        for (const auto& edge : edges)
        {
            int a = edge[0];
            int b = edge[1];

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        // check how many nodes and vertices in group
        // 1 and 2 nodes will be counted as completed components.
        std::vector<bool> visited(n, false);
        int               completeCount = 0;

        auto dfs = [&](auto& self, int curr, int& nodes, int& edgesCount) -> void
        {
            visited[curr] = true;
            nodes++;
            edgesCount += adj[curr].size();
            for (int next : adj[curr])
            {
                if (!visited[next])
                    self(self, next, nodes, edgesCount);
            }
        };

        for (int i = 0; i < n; i++)
        {
            if (visited[i])
                continue;
            int nodes = 0, edgesCount = 0;
            dfs(dfs, i, nodes, edgesCount);
            if (edgesCount == nodes * (nodes - 1))
                completeCount++;
        }

        return completeCount;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    int                           n1        = 6;
    std::vector<std::vector<int>> edges1    = {{0, 1}, {0, 2}, {1, 2}, {3, 4}};
    int                           expected1 = 3;
    int                           output1;

    int                           n2        = 6;
    std::vector<std::vector<int>> edges2    = {{0, 1}, {0, 2}, {1, 2}, {3, 4}, {3, 5}};
    int                           expected2 = 1;
    int                           output2;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.countCompleteComponents(n1, edges1); });
    double t2 = timeIt([&]() { output2 = s.countCompleteComponents(n2, edges2); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);

    return 0;
}