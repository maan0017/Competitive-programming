#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  public:
    // for binary table
    int                 rows, cols;
    vector<vector<int>> ancestorTable; // sparse table

    int customUpperBound(vector<pair<int, int>>& arr, int target)
    {
        int n      = arr.size();
        int l      = 0;
        int r      = n - 1;
        int result = 0;

        while (l <= r)
        {
            int mid = l + (r - l) / 2;

            if (arr[mid].first <= target)
            {
                result = mid;
                l      = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }

        return result;
    }

    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                     vector<vector<int>>& queries)
    {
        //arr
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = {nums[i], i};
        }

        sort(arr.begin(), arr.end());
        vector<int> nodeToIdx(n);
        for (int i = 0; i < n; i++)
        {
            int node        = arr[i].second;
            nodeToIdx[node] = i;
            // nodeToIdx[arr[i].second] = i;
        }

        rows = n;
        cols = log2(n) + 1;
        ancestorTable.resize(rows, vector<int>(cols, 0));

        // fill the 0th column first
        for (int node = 0; node < n; node++)
            ancestorTable[node][0] = customUpperBound(arr, arr[node].first + maxDiff);

        // fill remaining columns.
        for (int j = 1; j < cols; j++)
        {
            for (int node = 0; node < n; node++)
            {
                ancestorTable[node][j] = ancestorTable[ancestorTable[node][j - 1]][j - 1];
            }
        }

        vector<int> result;
        for (auto& query : queries)
        {
            int u = query[0];
            int v = query[1];

            int a = nodeToIdx[u];
            int b = nodeToIdx[v];

            if (a == b)
            {
                result.push_back(0);
                continue;
            }

            if (a > b)
                swap(a, b);

            int curr  = a;
            int jumps = 0;

            for (int j = cols - 1; j >= 0; j--)
            {
                if (ancestorTable[curr][j] < b)
                {
                    curr = ancestorTable[curr][j];
                    jumps += (1 << j); // pow(2, j) == 2^j
                }
            }

            if (ancestorTable[curr][0] >= b)
                result.push_back(jumps + 1);
            else
                result.push_back(-1);
        }

        return result;
    }
};

class SolutionOptimal
{
  public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                     vector<vector<int>>& queries)
    {
        // 1. Edge Case: If maxDiff is negative, no edges can possibly exist in the graph.
        if (maxDiff < 0)
        {
            return vector<int>(queries.size(), -1);
        }

        // 2. Extract, sort, and deduplicate all unique values
        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        int V = vals.size();

        // 3. Build Connected Components to answer reachability instantly
        vector<int> comp(V, 0);
        for (int i = 1; i < V; ++i)
        {
            if (1LL * vals[i] - vals[i - 1] <= maxDiff)
            {
                comp[i] = comp[i - 1];
            }
            else
            {
                comp[i] = comp[i - 1] + 1;
            }
        }

        // 4. Cache-Friendly Binary Lifting Setup
        // Transposed from up[V][maxJumps] to up[maxJumps][V] for massive performance gains.
        // It requires only 20 contiguous memory allocations instead of 100,000.
        int                 maxJumps = 20;
        vector<vector<int>> up(maxJumps, vector<int>(V, 0));

        // Base case (2^0 = 1 step) using a sliding window
        int right = 0;
        for (int i = 0; i < V; ++i)
        {
            // right monotonically increases, achieving O(V) time
            while (right + 1 < V && 1LL * vals[right + 1] - vals[i] <= maxDiff)
            {
                right++;
            }
            up[0][i] = right;
        }

        // Precompute jumps for 2^1, 2^2, ..., 2^19 steps
        for (int j = 1; j < maxJumps; ++j)
        {
            for (int i = 0; i < V; ++i)
            {
                up[j][i] = up[j - 1][up[j - 1][i]];
            }
        }

        // 5. Process Queries
        vector<int> ans;
        ans.reserve(queries.size()); // Pre-allocate to prevent dynamic resizing overhead

        for (const auto& q : queries)
        {
            int u = q[0], v = q[1];

            // Exact same node -> 0 edges required
            if (u == v)
            {
                ans.push_back(0);
                continue;
            }

            int valU = nums[u];
            int valV = nums[v];

            // Different nodes but identical values -> 1 edge required
            // (Because |valU - valV| = 0, which is <= maxDiff)
            if (valU == valV)
            {
                ans.push_back(1);
                continue;
            }

            // Ensure we are always jumping left-to-right
            if (valU > valV)
            {
                swap(valU, valV);
            }

            // Map the values back to their unique indices in O(log V)
            int L = lower_bound(vals.begin(), vals.end(), valU) - vals.begin();
            int R = lower_bound(vals.begin(), vals.end(), valV) - vals.begin();

            // Reachability check
            if (comp[L] != comp[R])
            {
                ans.push_back(-1);
                continue;
            }

            // 6. Binary Lifting Jump Simulation
            int steps = 0;
            int curr  = L;

            for (int j = maxJumps - 1; j >= 0; --j)
            {
                // Notice the transposed access: up[j][curr]
                if (up[j][curr] < R)
                {
                    curr = up[j][curr];
                    steps += (1 << j);
                }
            }

            // We've jumped to the maximum node strictly before R.
            // Exactly 1 more jump guarantees we reach or exceed R.
            ans.push_back(steps + 1);
        }

        return ans;
    }
};
int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    int                 n1        = 5;
    vector<int>         nums1     = {1, 8, 3, 4, 2};
    int                 maxDiff1  = 3;
    vector<vector<int>> queries1  = {{0, 3}, {2, 4}};
    vector<int>         expected1 = {1, 1};
    vector<int>         output1;

    int                 n2        = 5;
    vector<int>         nums2     = {5, 3, 1, 9, 10};
    int                 maxDiff2  = 2;
    vector<vector<int>> queries2  = {{0, 1}, {0, 2}, {2, 3}, {4, 3}};
    vector<int>         expected2 = {1, 2, -1, 1};
    vector<int>         output2;

    int                 n3        = 3;
    vector<int>         nums3     = {3, 6, 1};
    int                 maxDiff3  = 1;
    vector<vector<int>> queries3  = {{0, 0}, {0, 1}, {1, 2}};
    vector<int>         expected3 = {0, -1, -1};
    vector<int>         output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.pathExistenceQueries(n1, nums1, maxDiff1, queries1); });
    double t2 = timeIt([&]() { output2 = s.pathExistenceQueries(n2, nums2, maxDiff2, queries2); });
    double t3 = timeIt([&]() { output3 = s.pathExistenceQueries(n3, nums3, maxDiff3, queries3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}