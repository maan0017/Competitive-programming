#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class Solution
{
  public:
    std::vector<int> sequentialDigits(int low, int high)
    {
        std::vector<int> result;

        // The lowest possible length is 2 (e.g., 12), highest is 9 (e.g., 123456789)
        for (int len = 2; len <= 9; ++len)
        {
            // The starting digit can be anything from 1 up to (10 - len)
            // For example, if len is 4, the max starting digit is 6 (6789)
            for (int start = 1; start <= 10 - len; ++start)
            {
                int num       = start;
                int nextDigit = start + 1;

                // Build the sequential number mathematically
                for (int i = 1; i < len; ++i)
                {
                    num = num * 10 + nextDigit;
                    nextDigit++;
                }

                // Check if it falls within the requested range
                if (num >= low && num <= high)
                {
                    result.push_back(num);
                }
            }
        }

        return result;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    int              low1 = 100, high1 = 300;
    std::vector<int> expected1 = {123, 234};
    std::vector<int> output1;

    int              low2 = 1000, high2 = 13000;
    std::vector<int> expected2 = {1234, 2345, 3456, 4567, 5678, 6789, 12345};
    std::vector<int> output2;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.sequentialDigits(low1, high1); });
    double t2 = timeIt([&]() { output2 = s.sequentialDigits(low2, high2); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);

    return 0;
}