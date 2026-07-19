#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class Solution
{
  public:
    std::string smallestSubsequence(std::string s)
    { // Store the last index of each character
        std::vector<int> lastIndex(26, -1);
        int              n = s.size();
        for (int i = 0; i < n; ++i)
        {
            lastIndex[s[i] - 'a'] = i;
        }

        // Keep track of characters currently in our result stack
        std::vector<bool> seen(26, false);

        // The result string will act as our monotonic stack
        std::string result = "";

        for (int i = 0; i < n; ++i)
        {
            char c = s[i];

            // If the character is already in our result, skip it
            if (seen[c - 'a'])
                continue;

            // While the result is not empty, AND the current character is smaller than the last added one,
            // AND the last added character appears again later in the string:
            while (!result.empty() && result.back() > c && lastIndex[result.back() - 'a'] > i)
            {
                // We can safely remove the larger character and add it back later
                seen[result.back() - 'a'] = false;
                result.pop_back();
            }

            // Add the current character to the result and mark it as seen
            result.push_back(c);
            seen[c - 'a'] = true;
        }

        return result;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    std::string s1        = "bcabc";
    std::string expected1 = "abc";
    std::string output1;

    std::string s2        = "cbacdcbc";
    std::string expected2 = "acdb";
    std::string output2;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.smallestSubsequence(s1); });
    double t2 = timeIt([&]() { output2 = s.smallestSubsequence(s2); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);

    return 0;
}