#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

#include <algorithm>
#include <vector>

class Solution
{
  public:
    std::vector<int> gcdValues(std::vector<int>& nums, std::vector<long long>& queries)
    {
        int n      = nums.size();
        int maxVal = *std::max_element(nums.begin(), nums.end());

        // 1. Calculate frequencies of each divisor
        std::vector<long long> divisorFreq(maxVal + 1, 0);
        for (int i = 0; i < n; i++)
        {
            int num = nums[i];
            for (int j = 1; j * j <= num; j++)
            {
                if (num % j == 0)
                {
                    divisorFreq[j]++;
                    int temp = num / j;
                    if (temp != j)
                    {
                        divisorFreq[temp]++;
                    }
                }
            }
        }

        // 2. Calculate exact number of pairs for each GCD using Inclusion-Exclusion
        std::vector<long long> pairsWithGCD(maxVal + 1, 0);
        for (int i = maxVal; i >= 1; i--)
        {
            long long count = divisorFreq[i];

            // Total pairs where 'i' is a common divisor
            pairsWithGCD[i] = count * (count - 1) / 2;

            // Subtract pairs where the actual GCD is a multiple of 'i'
            for (int multi = 2 * i; multi <= maxVal; multi += i)
            {
                pairsWithGCD[i] -= pairsWithGCD[multi];
            }
        }

        // 3. Build the prefix sum array
        std::vector<long long> prefixCountGCD(maxVal + 1, 0);
        for (int i = 1; i <= maxVal; i++)
        {
            prefixCountGCD[i] = pairsWithGCD[i] + prefixCountGCD[i - 1];
        }

        // 4. Answer the queries using Binary Search (std::upper_bound)
        std::vector<int> answer;
        answer.reserve(queries.size());

        for (long long idx : queries)
        {
            // upper_bound finds the first element strictly greater than 'idx'
            // Its index perfectly corresponds to our actual GCD value.
            int gcd_val = std::upper_bound(prefixCountGCD.begin(), prefixCountGCD.end(), idx) -
                          prefixCountGCD.begin();
            answer.push_back(gcd_val);
        }

        return answer;
    }
};

class BruteForceSolution
{
  public:
    std::vector<int> gcdValues(std::vector<int>& nums, std::vector<long long>& queries)
    {
        /* CONSTRAINTS
        2 <= n == nums.length <= 10^5
        1 <= nums[i] <= 5 * 10^4
        1 <= queries.length <= 10^5
        0 <= queries[i] < n * (n - 1) / 2
        */

        int n = nums.size();

        std::vector<int> gcdPairs;

        // 1. calculate gcd pairs.
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                gcdPairs.push_back(std::gcd(nums[i], nums[j]));
            }
        }

        std::sort(gcdPairs.begin(), gcdPairs.end());
        std::vector<int> answer(n);
        for (int i = 0; i < n; i++)
            answer[i] = gcdPairs[queries[i]];

        return answer;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    std::vector<int>       nums1     = {2, 3, 4};
    std::vector<long long> queries1  = {0, 2, 2};
    std::vector<int>       expected1 = {1, 2, 2};
    std::vector<int>       output1;

    std::vector<int>       nums2     = {4, 4, 2, 1};
    std::vector<long long> queries2  = {5, 3, 1, 0};
    std::vector<int>       expected2 = {4, 2, 1, 1};
    std::vector<int>       output2;

    std::vector<int>       nums3     = {2, 2};
    std::vector<long long> queries3  = {0, 0};
    std::vector<int>       expected3 = {2, 2};
    std::vector<int>       output3;

    std::vector<int>       nums4     = {1, 4};
    std::vector<long long> queries4  = {0};
    std::vector<int>       expected4 = {1};
    std::vector<int>       output4;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.gcdValues(nums1, queries1); });
    double t2 = timeIt([&]() { output2 = s.gcdValues(nums2, queries2); });
    double t3 = timeIt([&]() { output3 = s.gcdValues(nums3, queries3); });
    double t4 = timeIt([&]() { output4 = s.gcdValues(nums4, queries4); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);
    displayTestCaseOutput(expected4, output4, t4);

    return 0;
}