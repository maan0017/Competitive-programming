#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class Solution
{
  public:
    int findGCD(std::vector<int>& nums)
    {
        /*
        2 <= nums.length <= 1000
        1 <= nums[i] <= 1000
        */

        auto [minVal, maxVal] = std::minmax_element(nums.begin(), nums.end());
        return std::gcd(*minVal, *maxVal);
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    std::vector<int> nums1     = {2, 5, 6, 9, 10};
    int              expected1 = 2;
    int              output1;

    std::vector<int> nums2     = {7, 5, 6, 8, 3};
    int              expected2 = 1;
    int              output2;

    std::vector<int> nums3     = {3, 3};
    int              expected3 = 3;
    int              output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.findGCD(nums1); });
    double t2 = timeIt([&]() { output2 = s.findGCD(nums2); });
    double t3 = timeIt([&]() { output3 = s.findGCD(nums3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}