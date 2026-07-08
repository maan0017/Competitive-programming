#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  public:
    int closestTarget(vector<string>& words, string target, int startIndex)
    {
        int n = words.size();

        int shortestDistance = n;

        for (int i = 0; i < n; i++)
        {
            if (words[i] != target)
                continue;

            // 1. Calculate the standard straight-line distance
            int directDistance = abs(i - startIndex);

            // 2. Calculate the distance going the opposite way around the circle
            int circularDistance = n - directDistance;

            // 3. Find the minimum and update the global shortest distance
            shortestDistance = min({shortestDistance, directDistance, circularDistance});
        }

        // If shortestDistance remained 'n', we never found the target
        if (shortestDistance == n)
            return -1;

        return shortestDistance;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    vector<string> words1      = {"hello", "i", "am", "leetcode", "hello"};
    string         target1     = "hello";
    int            startIndex1 = 1;
    int            expected1   = 1;
    int            output1;

    vector<string> words2      = {"a", "b", "leetcode"};
    string         target2     = "leetcode";
    int            startIndex2 = 0;
    int            expected2   = 1;
    int            output2;

    vector<string> words3      = {"i", "eat", "leetcode"};
    string         target3     = "ate";
    int            startIndex3 = 0;
    int            expected3   = -1;
    int            output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.closestTarget(words1, target1, startIndex1); });
    double t2 = timeIt([&]() { output2 = s.closestTarget(words2, target2, startIndex2); });
    double t3 = timeIt([&]() { output3 = s.closestTarget(words3, target3, startIndex3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}