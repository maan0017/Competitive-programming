#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  public:
    int numberOfSubstrings(string s)
    {
        int n = s.size();
        if (n < 3)
            return 0;

        int lastSeen[3] = {-1, -1, -1};
        int count       = 0;
        int min_index   = -1;

        for (int i = 0; i < n; i++)
        {
            lastSeen[s[i] - 'a'] = i;

            min_index = min({lastSeen[0], lastSeen[1], lastSeen[2]});

            if (min_index != -1)
                count += (min_index + 1);
        }

        return count;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here

    Solution s;
    // call that function here ->

    string s1        = "abcabc";
    int    expected1 = 10;
    int    output1;

    string s2        = "aaacb";
    int    expected2 = 3;
    int    output2;

    string s3        = "abc";
    int    expected3 = 1;
    int    output3;

    double t1 = timeIt([&]() { output1 = s.numberOfSubstrings(s1); });
    double t2 = timeIt([&]() { output2 = s.numberOfSubstrings(s2); });
    double t3 = timeIt([&]() { output3 = s.numberOfSubstrings(s3); });

    displayTestCaseOutput(1, expected1, output1, t1);
    displayTestCaseOutput(2, expected2, output2, t2);
    displayTestCaseOutput(3, expected3, output3, t3);

    return 0;
}