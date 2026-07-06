#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  public:
    int maximumSafenessFactor(vector<vector<int>>& grid)
    {
        int n = grid.size();

        // If the start or end cell has a thief, the minimum safeness is 0
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
            return 0;

        vector<vector<int>>   dist(n, vector<int>(n, -1));
        queue<pair<int, int>> q;

        // Step 1: Multi-source BFS to find min distance to any thief
        for (int r = 0; r < n; ++r)
        {
            for (int c = 0; c < n; ++c)
            {
                if (grid[r][c] == 1)
                {
                    q.push({r, c});
                    dist[r][c] = 0;
                }
            }
        }

        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        while (!q.empty())
        {
            auto [r, c] = q.front();
            q.pop();

            for (auto& dir : dirs)
            {
                int nr = r + dir[0];
                int nc = c + dir[1];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1)
                {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        // Step 2: Max-Heap (Dijkstra-style) to find the path with max minimum safeness
        priority_queue<pair<int, pair<int, int>>> pq;
        pq.push({dist[0][0], {0, 0}}); // {safeness_factor, {r, c}}

        vector<vector<bool>> visited(n, vector<bool>(n, false));
        visited[0][0] = true;

        while (!pq.empty())
        {
            auto [safe, cell] = pq.top();
            pq.pop();

            int r = cell.first;
            int c = cell.second;

            // If we've reached the bottom-right corner, we return the max safeness path
            if (r == n - 1 && c == n - 1)
            {
                return safe;
            }

            for (auto& dir : dirs)
            {
                int nr = r + dir[0];
                int nc = c + dir[1];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc])
                {
                    visited[nr][nc] = true;
                    // The safeness of a path is the minimum safeness of all its cells
                    int min_safe = min(safe, dist[nr][nc]);
                    pq.push({min_safe, {nr, nc}});
                }
            }
        }

        return 0;
    }
};

static const auto fast_io = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}();

int main()
{
    // your test cases her
    std::vector<std::vector<int>> grid1     = {{1, 0, 0}, {0, 0, 0}, {0, 0, 1}};
    int                           expected1 = 0;
    int                           output1;

    std::vector<std::vector<int>> grid2     = {{0, 0, 1}, {0, 0, 0}, {0, 0, 0}};
    int                           expected2 = 2;
    int                           output2;

    std::vector<std::vector<int>> grid3 = {{0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}};
    int                           expected3 = 2;
    int                           output3;

    // call that function here ->
    Solution s;
    double   t1 = timeIt([&]() { output1 = s.maximumSafenessFactor(grid1); });
    double   t2 = timeIt([&]() { output2 = s.maximumSafenessFactor(grid2); });
    double   t3 = timeIt([&]() { output3 = s.maximumSafenessFactor(grid3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}