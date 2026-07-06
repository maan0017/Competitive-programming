#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  public:
    int removeCoveredIntervals(vector<vector<int>>& arr)
    {
        // 1. sort a[0] <= b[0] and a[1] >= b[1]
        sort(arr.begin(), arr.end(),
             [](vector<int>& a, vector<int>& b)
             {
                 if (a[0] == b[0])
                     return a[1] > b[1];
                 return a[0] < b[0];
             });

        int count   = 1;
        int lastEnd = arr[0][1];

        for (int i = 1; i < (int) arr.size(); i++)
        {
            if (lastEnd >= arr[i][1])
                continue;

            lastEnd = arr[i][1];
            count++;
        }

        return count;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    vector<vector<int>> arr1      = {{1, 4}, {3, 6}, {2, 8}};
    int                 expected1 = 2;
    int                 output1;

    vector<vector<int>> arr2      = {{1, 4}, {2, 3}};
    int                 expected2 = 1;
    int                 output2;

    vector<vector<int>> arr3      = {{1, 2}, {1, 4}, {3, 4}};
    int                 expected3 = 1;
    int                 output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.removeCoveredIntervals(arr1); });
    double t2 = timeIt([&]() { output2 = s.removeCoveredIntervals(arr2); });
    double t3 = timeIt([&]() { output3 = s.removeCoveredIntervals(arr3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}