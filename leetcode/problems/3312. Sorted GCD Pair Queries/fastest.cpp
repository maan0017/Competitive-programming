// Force the compiler to use maximum optimization, unroll loops, and use advanced CPU instructions
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

// Allocate memory globally exactly ONCE.
// Max nums[i] is 50,000. 50005 provides a safe buffer.
constexpr int MAX_VAL = 50005;
int           divisorCount[MAX_VAL];
long long     gcdPairs[MAX_VAL];

// Fast I/O trick: Disables C/C++ stream synchronization before main() runs
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

class Solution
{
  public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries)
    {
        int max_val = 0;

        // 1. Count frequencies and find the maximum number
        for (int x : nums)
        {
            if (x > max_val)
                max_val = x;
            divisorCount[x]++;
        }

        // 2. Sieve trick to find all multiples in O(M log M) time
        for (int x = 1; x <= max_val; ++x)
        {
            for (int y = 2 * x; y <= max_val; y += x)
            {
                divisorCount[x] += divisorCount[y];
            }
        }

        // 3. Count Pairs and subtract invalid multiples (Inclusion-Exclusion)
        for (int x = max_val; x >= 1; --x)
        {
            long long cnt = divisorCount[x];
            // >> 1 is a bitwise shift, exactly equivalent to / 2 but slightly faster
            gcdPairs[x] = (cnt * (cnt - 1LL)) >> 1;

            for (int y = 2 * x; y <= max_val; y += x)
            {
                gcdPairs[x] -= gcdPairs[y];
            }
        }

        // 4. Prefix Sum for binary search
        for (int i = 2; i <= max_val; ++i)
        {
            gcdPairs[i] += gcdPairs[i - 1];
        }

        // 5. Answer Queries via Binary Search (upper_bound)
        int         q_size = queries.size();
        vector<int> ans(q_size);
        for (int i = 0; i < q_size; ++i)
        {
            // pointer arithmetic: upper_bound returns an iterator, subtract the base pointer to get the index
            ans[i] = upper_bound(gcdPairs + 1, gcdPairs + max_val + 1, queries[i]) - gcdPairs;
        }

        // 6. Reset only the memory we touched so it's clean for the next LeetCode testcase
        memset(divisorCount, 0, (max_val + 1) * sizeof(int));

        return ans;
    }
};