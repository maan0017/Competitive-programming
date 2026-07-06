#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;

class Solution
{
  public:
    long long countMajoritySubarrays(vector<int>& nums, int target)
    {
        unordered_map<int, int> mp; // cummaletiv sum -> Count

        int cumSum = 0;
        mp[0]      = 1;

        long long validLeftPoints = 0;
        long long result          = 0;

        for (size_t j = 0; j < nums.size(); j++)
        {
            if (nums[j] == target)
            {
                validLeftPoints += mp[cumSum];
                cumSum += 1;
            }
            else
            {
                cumSum -= 1;
                validLeftPoints -= mp[cumSum];
            }

            mp[cumSum] += 1;
            result += validLeftPoints;
        }

        return result;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    vector<int> nums1     = {1, 2, 2, 3};
    int         target1   = 2;
    int         expected1 = 5;

    vector<int> nums2     = {1, 1, 1, 1};
    int         target2   = 1;
    int         expected2 = 10;

    vector<int> nums3     = {1, 2, 3};
    int         target3   = 4;
    int         expected3 = 0;

    Solution s;
    // call that function here ->
    long long output1 = s.countMajoritySubarrays(nums1, target1);
    long long output2 = s.countMajoritySubarrays(nums2, target2);
    long long output3 = s.countMajoritySubarrays(nums3, target3);

    if (expected1 == output1)
    {
        cout << "Test case passed" << endl;
    }
    else
    {
        cout << "Test case failed" << endl;
        cout << "       Expected:" << expected1 << endl;
        cout << "       Output:" << output1 << endl;
    }

    if (expected2 == output2)
    {
        cout << "Test case passed" << endl;
    }
    else
    {
        cout << "Test case failed" << endl;
        cout << "       Expected:" << expected2 << endl;
        cout << "       Output:" << output2 << endl;
    }

    if (expected3 == output3)
    {
        cout << "Test case passed" << endl;
    }
    else
    {
        cout << "Test case failed" << endl;
        cout << "       Expected:" << expected3 << endl;
        cout << "       Output:" << output3 << endl;
    }

    return 0;
}