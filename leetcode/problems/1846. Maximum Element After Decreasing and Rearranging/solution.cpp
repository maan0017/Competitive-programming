#include "../displayOutputs.h"
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <vector>
using namespace std;

// ─── Solution ────────────────────────────────────────────────────────────────

class Solution
{
  public:
    int maximumElementAfterDecrementingAndRearranging(std::vector<int>& arr)
    {
        int n = arr.size();

        sort(arr.begin(), arr.end());

        // special condition, 1st element must be 1.
        if (arr[0] != 1)
            arr[0] = 1;

        for (int i = 1; i < n; i++)
        {
            int gap = abs(arr[i] - arr[i - 1]);
            if (gap >= 2)
            {
                arr[i] = arr[i - 1] + 1;
            }
        }

        return arr.back();
    }
};

class SolutionOptimal
{
  public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr)
    {
        int n = arr.size();

        // Step 1: Initialize frequency array
        vector<int> counts(n + 1, 0);

        // Step 2: Count frequencies (cap at n)
        for (int num : arr)
        {
            counts[min(num, n)]++;
        }

        // Step 3: Calculate the max element greedily
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            // We can add counts[i] to our answer, but we cannot exceed 'i'
            ans = min(ans + counts[i], i);
        }

        return ans;
    }
};

// ─── Main ─────────────────────────────────────────────────────────────────────

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto programStart = std::chrono::steady_clock::now();

    SolutionOptimal s;

    // ── Test case 1 ──────────────────────────────────────────────────────────
    std::vector<int> arr1      = {2, 2, 1, 2, 1};
    int              expected1 = 2;
    int              output1;

    double ms1 = timeIt([&] { output1 = s.maximumElementAfterDecrementingAndRearranging(arr1); });
    displayTestCaseOutput(1, expected1, output1, ms1);

    // ── Test case 2 ──────────────────────────────────────────────────────────
    std::vector<int> arr2      = {100, 1, 1000};
    int              expected2 = 3;
    int              output2;

    double ms2 = timeIt([&] { output2 = s.maximumElementAfterDecrementingAndRearranging(arr2); });
    displayTestCaseOutput(2, expected2, output2, ms2);

    // ── Program total ─────────────────────────────────────────────────────────
    double totalMs =
        std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - programStart)
            .count();

    std::cout << "\nTotal runtime: " << totalMs << " ms\n";
    return 0;
}