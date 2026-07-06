#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  public:
    bool findSafeWalk(vector<vector<int>>& grid, int health)
    {
        int m = grid.size();
        int n = grid[0].size();

        // 1. Create a 2D array to track the minimum damage to reach each cell.
        // Initialize all cells to INT_MAX.
        vector<vector<int>> min_damage(m, vector<int>(n, INT_MAX));

        // 2. Initialize the deque
        deque<pair<int, int>> dq;

        // 3. Initialize the starting position
        dq.push_back({0, 0});
        min_damage[0][0] = grid[0][0]; // Takes 1 damage if the start cell is a '1'

        // Direction vectors for moving Up, Down, Left, Right
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // 4. Begin exploration
        while (!dq.empty())
        {
            // Get the cell currently at the front of the deque
            auto [r, c] = dq.front();
            dq.pop_front();

            // Check all 4 adjacent neighbors
            for (auto& dir : dirs)
            {
                int nr = r + dir[0];
                int nc = c + dir[1];

                // Ensure the neighbor is within grid boundaries
                if (nr >= 0 && nr < m && nc >= 0 && nc < n)
                {
                    // Calculate what the damage WOULD be to move to this neighbor
                    int new_damage = min_damage[r][c] + grid[nr][nc];

                    // If we found a strictly better (lower damage) path to this neighbor, update it
                    if (new_damage < min_damage[nr][nc])
                    {
                        min_damage[nr][nc] = new_damage;

                        // The Core 0-1 BFS Logic:
                        // If it costs 0 damage, prioritize it by pushing to the front.
                        // If it costs 1 damage, delay it by pushing to the back.
                        if (grid[nr][nc] == 0)
                            dq.push_front({nr, nc});
                        else
                            dq.push_back({nr, nc});
                    }
                }
            }
        }

        // 5. Final Check: Did we reach the end with at least 1 health remaining?
        int final_damage = min_damage[m - 1][n - 1];
        return (health - final_damage) >= 1;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    vector<vector<int>> grid1     = {{0, 1, 0, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 1, 0}};
    int                 health1   = 1;
    bool                expected1 = true;
    bool                output1;

    vector<vector<int>> grid2 = {
        {0, 1, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0}, {0, 1, 1, 1, 0, 1}, {0, 0, 1, 0, 1, 0}};
    int  health2   = 3;
    bool expected2 = false;
    bool output2;

    vector<vector<int>> grid3     = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    int                 health3   = 5;
    bool                expected3 = true;
    bool                output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.findSafeWalk(grid1, health1); });
    double t2 = timeIt([&]() { output2 = s.findSafeWalk(grid2, health2); });
    double t3 = timeIt([&]() { output3 = s.findSafeWalk(grid3, health3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}