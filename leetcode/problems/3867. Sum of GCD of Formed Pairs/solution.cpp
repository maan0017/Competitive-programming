#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class Solution
{
  public:
    long long gcdSum(std::vector<int>& nums)
    {
        // CONSTRAINTS
        // 1 <= n == nums.length <= 10^5
        // 1 <= nums[i] <= 10​​​​​​​9
        int n = nums.size();

        std::vector<int> prefixGcd(n);
        int              maxi = 1;

        for (int i = 0; i < n; i++)
        {
            maxi         = std::max(nums[i], maxi);
            prefixGcd[i] = std::gcd(nums[i], maxi);
        }

        std::sort(prefixGcd.begin(), prefixGcd.end());

        long long gcdSum = 0;

        // int       left = 0, right = n - 1;
        // while (left < right)
        // {
        //     gcdSum += std::gcd(prefixGcd[left], prefixGcd[right]);
        //     left++;
        //     right--;
        // }
        for (int i = 0; i < n / 2; i++)
            gcdSum += std::gcd(prefixGcd[i], prefixGcd[n - 1 - i]);

        return gcdSum;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    std::vector<int> nums1     = {2, 6, 4};
    long long        expected1 = 2;
    long long        output1;

    std::vector<int> nums2     = {3, 6, 2, 8};
    long long        expected2 = 5;
    long long        output2;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.gcdSum(nums1); });
    double t2 = timeIt([&]() { output2 = s.gcdSum(nums2); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);

    return 0;
}