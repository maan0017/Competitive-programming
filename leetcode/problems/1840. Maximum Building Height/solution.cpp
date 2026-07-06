#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
typedef vector<vector<int>> matrix;

class Solution
{
  public:
    int maxBuilding(int n, vector<vector<int>>& restrictions)
    {
        int m = restrictions.size();
        if (!m)
            return n - 1;

        std::sort(restrictions.begin(), restrictions.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) { return a[0] < b[0]; });
        if (restrictions[m - 1][0] != n)
            restrictions.push_back({n, INT_MAX});

        int maxHeight = 0;

        int currentHeight = 0;
        int peak          = 0;
        int distance      = restrictions[0][0];
        int allowed       = restrictions[0][1];
        // first
        {
            peak      = allowed + (distance - allowed) / 2;
            maxHeight = max(peak, maxHeight);
            if (peak > allowed)
                currentHeight = allowed;
            else
                currentHeight += distance;
        }

        // in between
        for (int i = 1; i < m; i++)
        {
            distance = restrictions[i][0] - restrictions[i - 1][0];
            allowed  = restrictions[i][1];

            // is gap bigger than maxAllowed
            if (currentHeight + distance <= allowed)
            {
                currentHeight += distance;
                maxHeight = max(currentHeight, maxHeight);
            }
            else
            {
                if (currentHeight > allowed)
                {
                    int gap       = currentHeight - allowed;
                    peak          = currentHeight + (distance - gap) / 2;
                    maxHeight     = max(peak, maxHeight);
                    currentHeight = allowed;
                }
                else
                {
                    int gap   = allowed - currentHeight;
                    peak      = currentHeight + gap + (distance - gap) / 2;
                    maxHeight = max(peak, maxHeight);
                    currentHeight += gap;
                }
            }
        }

        return maxHeight;
    }
};

class OptimalSolution
{
  public:
    int maxBuilding(int n, vector<vector<int>>& restrictions)
    {
        // 1. Add implicit boundary restrictions
        restrictions.push_back({1, 0});
        restrictions.push_back({n, n - 1}); // A building's height can never exceed its id - 1

        // 2. Sort restrictions by building ID
        sort(restrictions.begin(), restrictions.end());

        int m = restrictions.size();

        // 3. Left-to-Right Pass
        for (int i = 1; i < m; ++i)
        {
            int dist           = restrictions[i][0] - restrictions[i - 1][0];
            restrictions[i][1] = min(restrictions[i][1], restrictions[i - 1][1] + dist);
        }

        // 4. Right-to-Left Pass
        for (int i = m - 2; i >= 0; --i)
        {
            int dist           = restrictions[i + 1][0] - restrictions[i][0];
            restrictions[i][1] = min(restrictions[i][1], restrictions[i + 1][1] + dist);
        }

        // 5. Calculate the maximum peak between all adjacent restrictions
        int maxHeight = 0;
        for (int i = 1; i < m; ++i)
        {
            int dist        = restrictions[i][0] - restrictions[i - 1][0];
            int leftHeight  = restrictions[i - 1][1];
            int rightHeight = restrictions[i][1];

            // Peak math: derived from leftHeight + x = rightHeight + (dist - x)
            int peak  = leftHeight + (dist + rightHeight - leftHeight) / 2;
            maxHeight = max(maxHeight, peak);
        }

        return maxHeight;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    int    n1            = 5;
    matrix restrcitions1 = {{2, 1}, {4, 1}};
    int    expected1     = 2;

    int    n2            = 6;
    matrix restrcitions2 = {};
    int    expected2     = 5;

    int    n3            = 10;
    matrix restrcitions3 = {{5, 3}, {2, 5}, {7, 4}, {10, 3}};
    int    expected3     = 5;

    Solution s;
    // call that function here ->
    int output1 = s.maxBuilding(n1, restrcitions1);
    int output2 = s.maxBuilding(n2, restrcitions2);
    int output3 = s.maxBuilding(n3, restrcitions3);

    if (output1 == expected1)
        std::cout << "test case 1 passed." << std::endl;
    else
        std::cout << "test case 1 failed." << std::endl;

    if (output2 == expected2)
        std::cout << "test case 2 passed." << std::endl;
    else
        std::cout << "test case 2 failed." << std::endl;

    if (output3 == expected3)
        std::cout << "test case 3 passed." << std::endl;
    else
        std::cout << "test case 3 failed." << std::endl;

    return 0;
}