#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class Solution
{
  public:
    int uniqueXorTriplets(std::vector<int>& nums)
    {
        int n = nums.size();

        if (n < 3)
            return n;

        // if maxVal >=3
        // [0, 2^(msb(n) + 1) - 1]
        // <<<   msb(n)=⌊log2​(n)⌋​    >>>
        // int ans = std::pow(2, std::log2(n) + 1) - 2;
        int ans = 1; // 2 ^ 0
        while (ans <= n)
            ans *= 2; // ans = (ans << 1);

        // Right Answer will be the nearest 2^x of n,
        return ans;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    std::vector<int> nums1     = {1, 2};
    int              expected1 = 2;
    int              output1;

    std::vector<int> nums2     = {3, 1, 2};
    int              expected2 = 4;
    int              output2;

    std::vector<int> nums3     = {3, 1, 2, 4};
    int              expected3 = 8;
    int              output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.uniqueXorTriplets(nums1); });
    double t2 = timeIt([&]() { output2 = s.uniqueXorTriplets(nums2); });
    double t3 = timeIt([&]() { output3 = s.uniqueXorTriplets(nums3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}