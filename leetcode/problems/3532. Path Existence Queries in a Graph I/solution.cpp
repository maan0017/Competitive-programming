#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                      vector<vector<int>>& queries)
    {
        vector<int> comps(n, -1);
        int         comp = 0;
        comps[0]         = comp;

        // 1st Loop : check and assign to it's component
        for (int i = 1; i < n; i++)
        {
            if (nums[i] - nums[i - 1] > maxDiff)
                ++comp;

            comps[i] = comp;
        }

        int          m = queries.size();
        vector<bool> ans(m, false);

        // 2nd loop: check if l and r are connected using the parent of the component group they lie in.
        for (int i = 0; i < m; i++)
        {
            if (comps[queries[i][0]] == comps[queries[i][1]])
                ans[i] = true;
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    int                 n1        = 2;
    vector<int>         nums1     = {1, 3};
    int                 maxDiff1  = 1;
    vector<vector<int>> queries1  = {{0, 0}, {0, 1}};
    vector<bool>        expected1 = {true, false};
    vector<bool>        output1;

    int                 n2        = 4;
    vector<int>         nums2     = {2, 5, 6, 8};
    int                 maxDiff2  = 2;
    vector<vector<int>> queries2  = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
    vector<bool>        expected2 = {false, false, true, true};
    vector<bool>        output2;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.pathExistenceQueries(n1, nums1, maxDiff1, queries1); });
    double t2 = timeIt([&]() { output2 = s.pathExistenceQueries(n2, nums2, maxDiff2, queries2); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);

    return 0;
}