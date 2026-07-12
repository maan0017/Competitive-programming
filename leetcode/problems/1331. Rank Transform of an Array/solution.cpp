#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class Solution
{
  public:
    std::vector<int> arrayRankTransform(std::vector<int>& arr)
    {
        int n = arr.size();

        std::vector<int> copyArr = arr;

        sort(copyArr.begin(), copyArr.end());
        std::unordered_map<int, int> mp;

        int pos = 1;
        for (int i = 0; i < n; i++)
        {
            mp[copyArr[i]] = pos++;
            while (i < n - 1 && copyArr[i] == copyArr[i + 1])
                i++;
        }

        std::vector<int> result(n);
        for (int i = 0; i < n; i++)
        {
            result[i] = mp[arr[i]];
        }

        return result;
    }
};

// optimal solution
class SolutionOptimal
{
  public:
    std::vector<int> arrayRankTransform(std::vector<int>& arr)
    {
        // 1. Create a copy and sort it
        std::vector<int> copyArr = arr;
        std::sort(copyArr.begin(), copyArr.end());

        // 2. Map elements to their rank
        std::unordered_map<int, int> mp;
        for (int num : copyArr)
        {
            // emplace only inserts if 'num' is not already in the map.
            // mp.size() + 1 perfectly handles the 1-based ranking!
            mp.emplace(num, mp.size() + 1);
        }

        // 3. Overwrite the original array to save space
        for (int i = 0; i < arr.size(); i++)
        {
            arr[i] = mp[arr[i]];
        }

        return arr;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    std::vector<int> arr1      = {40, 10, 20, 30};
    std::vector<int> expected1 = {4, 1, 2, 3};
    std::vector<int> output1;

    std::vector<int> arr2      = {100, 100, 100};
    std::vector<int> expected2 = {1, 1, 1};
    std::vector<int> output2;

    std::vector<int> arr3      = {37, 12, 28, 9, 100, 56, 80, 5, 12};
    std::vector<int> expected3 = {5, 3, 4, 2, 8, 6, 7, 1, 3};
    std::vector<int> output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.arrayRankTransform(arr1); });
    double t2 = timeIt([&]() { output2 = s.arrayRankTransform(arr2); });
    double t3 = timeIt([&]() { output3 = s.arrayRankTransform(arr3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}