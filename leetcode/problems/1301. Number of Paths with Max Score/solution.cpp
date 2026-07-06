#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  public:
    vector<int> pathsWithMaxScore(vector<string>& board)
    {
        int n   = board.size();
        int MOD = 1e9 + 7;

        // dp[r][c].first = max_score, dp[r][c].second = number_of_ways
        // Initialize with (n+1) x (n+1) to easily handle edges.
        // A max_score of -1 indicates the cell is unreachable.
        vector<vector<pair<int, int>>> dp(n + 1, vector<pair<int, int>>(n + 1, {-1, 0}));

        // Base case: Starting at bottom-right ('S')
        dp[n - 1][n - 1] = {0, 1};

        // Traverse the board from bottom-right to top-left
        for (int r = n - 1; r >= 0; --r)
        {
            for (int c = n - 1; c >= 0; --c)
            {
                // Skip the starting cell and obstacles
                if (board[r][c] == 'S' || board[r][c] == 'X')
                {
                    continue;
                }

                int max_prev_score = -1;
                int ways           = 0;

                // The 3 possible cells we could have arrived from: Down, Right, Down-Right
                pair<int, int> prev_states[3] = {dp[r + 1][c], dp[r][c + 1], dp[r + 1][c + 1]};

                // Find the maximum score among reachable previous cells
                for (const auto& state : prev_states)
                {
                    int prev_score = state.first;
                    int prev_ways  = state.second;

                    if (prev_score > max_prev_score)
                    {
                        max_prev_score = prev_score;
                        ways           = prev_ways;
                    }
                    else if (prev_score == max_prev_score && prev_score != -1)
                    {
                        ways = (ways + prev_ways) % MOD;
                    }
                }

                // If the current cell is reachable from at least one valid path
                if (max_prev_score != -1)
                {
                    // 'E' adds 0 to the score, otherwise convert char to int
                    int current_score = (board[r][c] == 'E') ? 0 : (board[r][c] - '0');
                    dp[r][c]          = {max_prev_score + current_score, ways};
                }
            }
        }

        // The answer is located at the target destination: top-left ('E')
        int total_ways = dp[0][0].second;
        int max_score  = dp[0][0].first;

        // If total_ways is 0, it means 'E' was unreachable
        if (total_ways == 0)
        {
            return {0, 0};
        }

        return {max_score, total_ways};
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    vector<string> board1    = {"E23", "2X2", "12S"};
    vector<int>    expected1 = {7, 1};
    vector<int>    output1;

    vector<string> board2    = {"E12", "1X1", "21S"};
    vector<int>    expected2 = {4, 2};
    vector<int>    output2;

    vector<string> board3    = {"E11", "XXX", "11S"};
    vector<int>    expected3 = {0, 0};
    vector<int>    output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.pathsWithMaxScore(board1); });
    double t2 = timeIt([&]() { output2 = s.pathsWithMaxScore(board2); });
    double t3 = timeIt([&]() { output3 = s.pathsWithMaxScore(board3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}