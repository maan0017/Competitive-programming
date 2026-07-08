#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  public:
    int maxDistance(vector<int>& colors)
    {
        int n       = colors.size();
        int maxDist = 0;

        // 1. Fix the first house, find the furthest different house from the right
        for (int i = n - 1; i >= 0; i--)
        {
            if (colors[i] != colors[0])
            {
                maxDist = i; // Since we start at 0, distance is just i - 0
                break;       // Found the furthest, no need to keep checking
            }
        }

        // 2. Fix the last house, find the furthest different house from the left
        for (int i = 0; i < n; i++)
        {
            if (colors[i] != colors[n - 1])
            {
                maxDist = max(maxDist, (n - 1) - i);
                break; // Found the furthest, no need to keep checking
            }
        }

        return maxDist;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    vector<int> colors1   = {1, 1, 1, 6, 1, 1, 1};
    int         expected1 = 3;
    int         output1;

    vector<int> colors2   = {1, 8, 3, 8, 3};
    int         expected2 = 4;
    int         output2;

    vector<int> colors3   = {0, 1};
    int         expected3 = 1;
    int         output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.maxDistance(colors1); });
    double t2 = timeIt([&]() { output2 = s.maxDistance(colors2); });
    double t3 = timeIt([&]() { output3 = s.maxDistance(colors3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}