#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

// class Solution {
// public:
//     void rotate(vector<int>& nums, int k) {
//         k = k % nums.size();
//         std::rotate(nums.begin(), nums.end() - k, nums.end());
//     }
// };

class Solution
{
  public:
    void rotate(std::vector<int>& nums, int k)
    {
        int n = nums.size();
        k %= n;

        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    std::vector<int> nums1     = {1, 2, 3, 4, 5, 6, 7};
    int              k1        = 3;
    std::vector<int> expected1 = {5, 6, 7, 1, 2, 3, 4};

    std::vector<int> nums2     = {-1, -100, 3, 99};
    int              k2        = 2;
    std::vector<int> expected2 = {3, 99, -1, -100};

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { s.rotate(nums1, k1); });
    double t2 = timeIt([&]() { s.rotate(nums2, k2); });

    displayTestCaseOutput(expected1, nums1, t1);
    displayTestCaseOutput(expected2, nums2, t2);

    return 0;
}