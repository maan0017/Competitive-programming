#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class Solution
{
  public:
    std::vector<std::vector<int>> shiftGrid(std::vector<std::vector<int>>& grid, int k)
    {
        int row = grid.size();    // rows
        int col = grid[0].size(); // cols
        int n   = row * col;
        k %= n;

        if (k == 0)
            return grid;

        auto reverse = [&](int i, int j)
        {
            while (i < j)
            {
                std::swap(grid[i / col][i % col], grid[j / col][j % col]);
                i++;
                j--;
            }
        };

        reverse(0, n - 1);
        reverse(0, k - 1);
        reverse(k, n - 1);

        return grid;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    // Test Case 1
    std::vector<std::vector<int>> grid1     = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int                           k1        = 1;
    std::vector<std::vector<int>> expected1 = {{9, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    std::vector<std::vector<int>> output1;

    // Test Case 2
    std::vector<std::vector<int>> grid2 = {
        {3, 8, 1, 9}, {19, 7, 2, 5}, {4, 6, 11, 10}, {12, 0, 21, 13}};
    int                           k2        = 4;
    std::vector<std::vector<int>> expected2 = {
        {12, 0, 21, 13}, {3, 8, 1, 9}, {19, 7, 2, 5}, {4, 6, 11, 10}};
    std::vector<std::vector<int>> output2;

    // Test Case 3
    std::vector<std::vector<int>> grid3     = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int                           k3        = 9;
    std::vector<std::vector<int>> expected3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<int>> output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.shiftGrid(grid1, k1); });
    double t2 = timeIt([&]() { output2 = s.shiftGrid(grid2, k2); });
    double t3 = timeIt([&]() { output3 = s.shiftGrid(grid3, k3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}