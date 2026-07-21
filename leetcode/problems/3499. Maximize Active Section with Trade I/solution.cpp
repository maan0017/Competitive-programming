#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class Solution
{
  public:
    int maxActiveSectionsAfterTrade(std::string s)
    {
        std::vector<int> inactiveBlocks;
        int              onesCount = std::count(s.begin(), s.end(), '1');

        int       i = 0;
        const int n = s.size();
        while (i < n)
        {
            if (s[i] == '0')
            {
                int start = i;
                while (i < n && s[i] == '0')
                    i++;

                inactiveBlocks.push_back(i - start);
            }
            else
                i++;
        }

        // find the max sum pair
        int       maxPairSum = 0;
        const int m          = inactiveBlocks.size();
        for (int i = 1; i < m; i++)
        {
            int sum    = inactiveBlocks[i - 1] + inactiveBlocks[i];
            maxPairSum = std::max(sum, maxPairSum);
        }

        return onesCount + maxPairSum;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    std::string s1        = "01";
    int         expected1 = 1;
    int         output1;

    std::string s2        = "0100";
    int         expected2 = 4;
    int         output2;

    std::string s3        = "1000100";
    int         expected3 = 7;
    int         output3;

    std::string s4        = "01010";
    int         expected4 = 4;
    int         output4;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.maxActiveSectionsAfterTrade(s1); });
    double t2 = timeIt([&]() { output2 = s.maxActiveSectionsAfterTrade(s2); });
    double t3 = timeIt([&]() { output3 = s.maxActiveSectionsAfterTrade(s3); });
    double t4 = timeIt([&]() { output4 = s.maxActiveSectionsAfterTrade(s4); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);
    displayTestCaseOutput(expected4, output4, t4);

    return 0;
}