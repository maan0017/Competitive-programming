#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;

class Solution
{
  public:
    int countMajoritySubarrays(vector<int>& nums, int target) { return 0; }
};

class Solution1 // Burte force + counting targets
{
  public:
    int countMajoritySubarrays(vector<int>& nums, int target)
    {
        int n   = nums.size();
        int ans = 0;

        for (int i = 0; i < n; i++)
        {
            int count = 0;
            for (int j = i; j < n; j++)
            {
                if (nums[j] == target)
                    count++;
                if (count > (j - i + 1) / 2)
                    ans++;
            }
        }

        return ans;
    }
};

class Solution2 // Improved > Burte force + counting targets - non targets > 0
{
  public:
    int countMajoritySubarrays(vector<int>& nums, int target)
    {
        int n   = nums.size();
        int ans = 0;

        for (int i = 0; i < n; i++)
        {
            int count = 0;
            for (int j = i; j < n; j++)
            {
                if (nums[j] == target)
                    count++;
                else
                    count--;
                if (count > 0)
                    ans++;
            }
        }

        return ans;
    }
};

class Solution3
{
  public:
    int countMajoritySubarrays(vector<int>& nums, int target)
    {
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            nums[i] = nums[i] == target ? 1 : -1;
        }
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

    Solution2 s;
    // call that function here ->
    int output1 = s.countMajoritySubarrays(nums1, target1);
    int output2 = s.countMajoritySubarrays(nums2, target2);
    int output3 = s.countMajoritySubarrays(nums3, target3);

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