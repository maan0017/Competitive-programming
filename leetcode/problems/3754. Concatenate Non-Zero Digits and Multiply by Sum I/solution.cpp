#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  public:
    long long sumAndMultiply(int n)
    {
        long long sum = 0;
        int       mul = 0;

        string nStr = to_string(n);

        for (const char& c : nStr)
        {
            if (c == '0')
                continue;

            sum *= 10;
            sum += c - '0';
            mul += c - '0';
        }

        return 1LL * sum * mul;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    int n1        = 10203004;
    int expected1 = 12340;
    int output1;

    int n2        = 1000;
    int expected2 = 1;
    int output2;

    int n3        = 65463628;
    int expected3 = -1676422176;
    int output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.sumAndMultiply(n1); });
    double t2 = timeIt([&]() { output2 = s.sumAndMultiply(n2); });
    double t3 = timeIt([&]() { output3 = s.sumAndMultiply(n3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}