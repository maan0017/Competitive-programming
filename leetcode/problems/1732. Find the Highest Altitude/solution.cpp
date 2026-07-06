#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;

class Solution
{
  public:
    int largestAltitude(vector<int>& gain)
    {
        int         n      = gain.size();
        int         maxSum = 0;
        vector<int> prefixSum(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            int sum      = gain[i - 1] + prefixSum[i - 1];
            maxSum       = max(sum, maxSum);
            prefixSum[i] = sum;
        }

        return maxSum;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    vector<int> data1     = {-5, 1, 5, 0, -7};
    int         expected1 = 1;

    vector<int> data2     = {-4, -3, -2, -1, 4, 3, 2};
    int         expected2 = 0;

    Solution s;
    // call that function here ->
    int output1 = s.largestAltitude(data1);
    int output2 = s.largestAltitude(data2);

    if (expected1 == output1)
        std::cout << "test case 1 passed." << std::endl;
    else
        std::cout << "test case 1 failed." << std::endl;

    if (expected2 == output2)
        std::cout << "test case 2 passed." << std::endl;
    else
        std::cout << "test case 2 failed." << std::endl;

    return 0;
}