#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  private:
    // Modulo constant required by the problem to prevent integer overflow
    int               M = 1e9 + 7;
    typedef long long ll;

  public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries)
    {
        int m = s.size();
        int n = queries.size();

        // Prefix arrays are sized m + 1 (1-based indexing) to easily handle
        // range queries without checking for out-of-bounds errors on index 0.

        // countDigit[i] stores the total number of non-zero digits up to index i
        vector<int> countDigit(m + 1, 0);

        // prefixSum[i] stores the modulo sum of all non-zero digits up to index i
        vector<ll> prefixSum(m + 1, 0);

        // numbersFormed[i] stores the integer formed by concatenating non-zero digits left-to-right
        vector<ll> numbersFormed(m + 1, 0);

        // pow10[i] precomputes (10^i) % M.
        // This replaces pow(10, k) to avoid floating-point inaccuracies and apply modulo correctly.
        vector<ll> pow10(m + 1, 1);

        // Step 1: Precompute all prefix arrays in a single pass O(m)
        for (int i = 0; i < m; i++)
        {
            // Compute the next power of 10 for string extraction later
            pow10[i + 1] = (pow10[i] * 10) % M;

            int num = s[i] - '0';

            if (num == 0)
            {
                // If the digit is 0, we do not add it to our new integer or sum.
                // We MUST carry the previous state forward so range subtractions remain accurate.
                countDigit[i + 1]    = countDigit[i];
                prefixSum[i + 1]     = prefixSum[i];
                numbersFormed[i + 1] = numbersFormed[i];
            }
            else
            {
                // If the digit is non-zero, increment the valid digit count
                countDigit[i + 1] = countDigit[i] + 1;

                // Add the digit to the running sum and apply modulo
                prefixSum[i + 1] = (prefixSum[i] + num) % M;

                // Shift the previous number left by multiplying by 10, then add the new digit.
                // Example: '1' then '2' -> (1 * 10) + 2 = 12. Apply modulo immediately.
                numbersFormed[i + 1] = (numbersFormed[i] * 10 + num) % M;
            }
        }

        vector<int> ans(n, 0);

        // Step 2: Process each query in O(1) time
        for (int i = 0; i < n; i++)
        {
            // queries[i] gives us a 0-based range.
            // We use l and r directly, but our prefix arrays are 1-based.
            // So prefix[r + 1] represents the end, and prefix[l] represents the start.
            int l = queries[i][0];
            int r = queries[i][1];

            // 'k' is the number of valid (non-zero) digits inside the query range [l, r]
            int k = countDigit[r + 1] - countDigit[l];

            // Extracting the substring integer mathematically:
            // If the string is "12345" and we want "45" (index 3 to 4):
            // We take "12345" and subtract "123" shifted to the left by k digits (k=2 here).
            // 12345 - (123 * 10^2) = 12345 - 12300 = 45.

            ll leftPart = (numbersFormed[l] * pow10[k]) % M;

            // In C++, modulo of negative numbers can yield negative results.
            // To fix (A - B) % M, we use the standard formula: (A - B % M + M) % M.
            ll num = (numbersFormed[r + 1] - leftPart + M) % M;

            // Extract the sum of the digits in the range, applying the same negative modulo fix.
            ll sum = (prefixSum[r + 1] - prefixSum[l] + M) % M;

            // The final answer is the extracted number multiplied by the digit sum, modulo M.
            ans[i] = (num * sum) % M;
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    string              s1        = "10203004";
    vector<vector<int>> queries1  = {{0, 7}, {1, 3}, {4, 6}};
    vector<int>         expected1 = {12340, 4, 9};
    vector<int>         output1;

    string              s2        = "1000";
    vector<vector<int>> queries2  = {{0, 3}, {1, 1}};
    vector<int>         expected2 = {1, 0};
    vector<int>         output2;

    string              s3        = "9876543210";
    vector<vector<int>> queries3  = {{0, 9}};
    vector<int>         expected3 = {444444137};
    vector<int>         output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.sumAndMultiply(s1, queries1); });
    double t2 = timeIt([&]() { output2 = s.sumAndMultiply(s2, queries2); });
    double t3 = timeIt([&]() { output3 = s.sumAndMultiply(s3, queries3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}