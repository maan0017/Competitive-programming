#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class Solution
{
  public:
    int subsequencePairCount(std::vector<int>& nums)
    {
        const int MOD = 1e9 + 7;

        // Find the maximum number to bound our GCD dimensions
        int max_val = 0;
        for (int x : nums)
        {
            max_val = std::max(max_val, x);
        }

        // dp[g1][g2] stores the number of valid pairs of subsequences
        // with GCD g1 and GCD g2 respectively.
        std::vector<std::vector<int>> dp(max_val + 1, std::vector<int>(max_val + 1, 0));

        // Base case: 1 way to have two empty subsequences
        dp[0][0] = 1;

        for (int x : nums)
        {
            // next_dp starts as a copy of dp (this handles the "skip" option)
            std::vector<std::vector<int>> next_dp = dp;

            for (int g1 = 0; g1 <= max_val; ++g1)
            {
                for (int g2 = 0; g2 <= max_val; ++g2)
                {
                    if (dp[g1][g2] == 0)
                        continue; // Skip unreachable states

                    // Option 2: Add x to the first subsequence
                    int nxt_g1          = (g1 == 0) ? x : std::gcd(g1, x);
                    next_dp[nxt_g1][g2] = (next_dp[nxt_g1][g2] + dp[g1][g2]) % MOD;

                    // Option 3: Add x to the second subsequence
                    int nxt_g2          = (g2 == 0) ? x : std::gcd(g2, x);
                    next_dp[g1][nxt_g2] = (next_dp[g1][nxt_g2] + dp[g1][g2]) % MOD;
                }
            }
            dp = std::move(next_dp);
        }

        // Sum up all states where both subsequences are non-empty (gcd > 0)
        // and have equal GCDs (g1 == g2)
        int ans = 0;
        for (int g = 1; g <= max_val; ++g)
        {
            ans = (ans + dp[g][g]) % MOD;
        }

        return ans;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    std::vector<int> nums1     = {1, 2, 3, 4};
    int              expected1 = 10;
    int              output1;

    std::vector<int> nums2     = {10, 20, 30};
    int              expected2 = 2;
    int              output2;

    std::vector<int> nums3     = {1, 1, 1, 1};
    int              expected3 = 50;
    int              output3;

    std::vector<int> nums4     = {24, 26, 25, 20, 27, 27, 27, 27, 20, 27, 21, 27, 25, 20, 20,
                                  23, 25, 21, 20, 29, 24, 21, 23, 25, 28, 21, 21, 28, 25, 21};
    int              expected4 = 99415636;
    int              output4;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.subsequencePairCount(nums1); });
    double t2 = timeIt([&]() { output2 = s.subsequencePairCount(nums2); });
    double t3 = timeIt([&]() { output3 = s.subsequencePairCount(nums3); });
    double t4 = timeIt([&]() { output4 = s.subsequencePairCount(nums4); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);
    displayTestCaseOutput(expected4, output4, t4);

    return 0;
}