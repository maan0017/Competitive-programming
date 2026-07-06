#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;

// ---- MY FIRST SOLUTION
// class Solution
// {
//   public:
//     vector<int> pivotArray(vector<int>& nums, int pivot)
//     {
//         vector<int> left;
//         vector<int> right;

//         for (const int& num : nums)
//         {
//             if (num < pivot)
//                 left.push_back(num);
//             else if (num > pivot)
//                 right.push_back(num);
//             else
//                 right.insert(right.begin(), num);
//         }

//         left.insert(left.end(), right.begin(), right.end());

//         return left;
//     }
// };

class Solution
{
  public:
    vector<int> pivotArray(vector<int>& nums, int pivot)
    {
        int n = nums.size();
        // Pre-fill the result array with the pivot value
        vector<int> result(n, pivot);

        int left  = 0;
        int right = n - 1;

        // i iterates forward for smaller elements
        // j iterates backward for larger elements
        for (int i = 0, j = n - 1; i < n; ++i, --j)
        {
            if (nums[i] < pivot)
            {
                result[left++] = nums[i];
            }
            if (nums[j] > pivot)
            {
                result[right--] = nums[j];
            }
        }

        return result;
    }
};

// <<<-- CONSTRAINTS -->>>
// 1 <= nums.length <= 10^5
// -10^6 <= nums[i] <= 10^6
// pivot equals to an element of nums.

void displayResult(int, const vector<int>& expected, const vector<int>& output);
int  main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    // test case 1
    vector<int> data1     = {9, 12, 5, 10, 14, 3, 10};
    int         pivot1    = 10;
    vector<int> expected1 = {9, 5, 3, 10, 10, 12, 14};

    // test case 2
    vector<int> data2     = {-3, 4, 3, 2};
    int         pivot2    = 2;
    vector<int> expected2 = {-3, 2, 4, 3};

    Solution s;
    // call that function here ->
    vector<int> output1 = s.pivotArray(data1, pivot1);
    vector<int> output2 = s.pivotArray(data2, pivot2);

    displayResult(1, expected1, output1);
    displayResult(2, expected2, output2);

    cout << endl;
    return 0;
}

void displayResult(int test_case_num, const vector<int>& expected, const vector<int>& output)
{
    std::cout << "\n-------------   Test Case " << test_case_num << "   -------------\n";

    if (!expected.size())
        return;
    std::cout << "expected = [ ";
    for (auto& num : expected)
        std::cout << num << " ";
    std::cout << "]\n";

    if (!output.size())
        return;
    std::cout << "output   = [ ";
    for (auto& num : output)
        std::cout << num << " ";
    std::cout << "]\n";
}
