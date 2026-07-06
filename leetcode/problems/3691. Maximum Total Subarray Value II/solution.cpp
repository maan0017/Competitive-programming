#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;

class Solution
{
  public:
    long long maxTotalValue(vector<int>& nums, int k)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        // 1. Build the Sparse Tables for O(1) Range Queries
        int                 max_log = 32 - __builtin_clz(n);
        vector<vector<int>> stMax(n, vector<int>(max_log));
        vector<vector<int>> stMin(n, vector<int>(max_log));

        for (int i = 0; i < n; ++i)
        {
            stMax[i][0] = nums[i];
            stMin[i][0] = nums[i];
        }

        for (int j = 1; j < max_log; ++j)
        {
            for (int i = 0; i + (1 << j) <= n; ++i)
            {
                stMax[i][j] = max(stMax[i][j - 1], stMax[i + (1 << (j - 1))][j - 1]);
                stMin[i][j] = min(stMin[i][j - 1], stMin[i + (1 << (j - 1))][j - 1]);
            }
        }

        // Lambda to execute O(1) queries using the Sparse Tables
        auto get_val = [&](int l, int r)
        {
            int len = r - l + 1;
            int p   = 31 - __builtin_clz(len); // log2(len)
            int mx  = max(stMax[l][p], stMax[r - (1 << p) + 1][p]);
            int mn  = min(stMin[l][p], stMin[r - (1 << p) + 1][p]);
            return mx - mn;
        };

        // 2. Setup the Max-Heap for the K-Way Merge
        struct Element
        {
            int  val;
            int  l;
            int  r;
            bool operator<(const Element& other) const
            {
                return val < other.val; // Max-Heap based on subarray value
            }
        };

        priority_queue<Element> pq;

        // Push the absolute best subarray for every starting index 'l'
        for (int l = 0; l < n; ++l)
        {
            pq.push({get_val(l, n - 1), l, n - 1});
        }

        // 3. Extract the top K subarrays
        long long total = 0;
        for (int i = 0; i < k; ++i)
        {
            if (pq.empty())
                break;
            Element top = pq.top();
            pq.pop();

            total += top.val;

            // If we can still shrink the subarray from the right,
            // calculate the next best value and push it to the heap.
            if (top.r - 1 >= top.l)
            {
                pq.push({get_val(top.l, top.r - 1), top.l, top.r - 1});
            }
        }

        return total;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your code here
    vector<int> data1     = {1, 3, 2};
    int         k1        = 2;
    long long   expected1 = 4;

    vector<int> data2     = {4, 2, 5, 1};
    int         k2        = 3;
    long long   expected2 = 12;

    vector<int> data3     = {11, 8};
    int         k3        = 2;
    long long   expected3 = 3;

    vector<int> data4     = {9, 9, 37};
    int         k4        = 3;
    long long   expected4 = 56;

    Solution  s;
    long long output1 = s.maxTotalValue(data1, k1);
    cout << "output 1:" << output1 << endl;

    return 0;
}