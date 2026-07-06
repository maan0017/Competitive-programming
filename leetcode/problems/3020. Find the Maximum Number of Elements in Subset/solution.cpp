// 3020 : find the maximum number of elements in subsets
#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;

class Solution
{
  public:
    int maximumLength(vector<int>& nums)
    {
        unordered_map<long long, int> mp;

        for (const int& num : nums)
        {
            mp[num]++;
        }

        int maxLen = 1;

        if (mp.count(1))
        {
            int ones = mp[1];
            // length should be odd
            if (ones % 2 == 0)
                ones--;
            maxLen = max(maxLen, ones);
        }

        for (auto const& [key, value] : mp)
        {
            if (key == 1)
                continue;

            long long curr       = key;
            int       currentLen = 0;

            while (mp.count(curr) && mp[curr] >= 2)
            {
                currentLen += 2;
                curr = curr * curr;
            }

            // Check how the sequence terminated
            if (mp.count(curr))
            {
                // If the next square exists but only appears once, it becomes the peak
                currentLen += 1;
            }
            else
            {
                // If the next square doesn't exist, the PREVIOUS number (which had >= 2)
                // becomes the peak, so we only use 1 of its copies instead of 2.
                currentLen -= 1;
            }

            maxLen = max(maxLen, currentLen);
        }

        return maxLen;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    vector<int> nums1     = {5, 4, 1, 2, 2};
    int         expected1 = 3;

    vector<int> nums2     = {1, 3, 2, 4};
    int         expected2 = 1;

    Solution s;
    // call that function here ->
    int output1 = s.maximumLength(nums1);
    int output2 = s.maximumLength(nums2);

    if (output1 == expected1)
        cout << "test case 1 passed" << endl;
    else
    {
        cout << "test case 1 failed" << endl;
        cout << "       Expected:" << expected1 << endl;
        cout << "         Output:" << output1 << endl;
    }

    if (output2 == expected2)
        cout << "test case 2 passed" << endl;
    else
    {
        cout << "test case 2 failed" << endl;
        cout << "       Expected:" << expected2 << endl;
        cout << "         Output:" << output2 << endl;
    }

    return 0;
}