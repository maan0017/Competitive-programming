#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class Solution
{
  public:
    int gcdOfOddEvenSums(int n)
    {
        /*
         * MATHEMATICAL PROOF FOR O(1) COMPLEXITY:
         * 
         * 1. The sum of the first 'n' odd numbers (1 + 3 + 5 + ... + 2n-1)
         *    is a known mathematical series that always equals n^2.
         *    sumOdd = n * n
         * 
         * 2. The sum of the first 'n' even numbers (2 + 4 + 6 + ... + 2n)
         *    can be factored as 2 * (1 + 2 + 3 + ... + n).
         *    Using the standard sum formula: 2 * (n * (n + 1) / 2) = n * (n + 1).
         *    sumEven = n^2 + n
         * 
         * 3. We need to find GCD(sumOdd, sumEven), which is GCD(n^2, n^2 + n).
         *    Using the Euclidean algorithm property: GCD(A, B) = GCD(A, B - A).
         *    GCD(n^2, n^2 + n) = GCD(n^2, (n^2 + n) - n^2) = GCD(n^2, n).
         * 
         * 4. Since n^2 is perfectly divisible by n, the greatest common 
         *    divisor of n^2 and n is simply n.
         * 
         * Therefore, the entire loop computation reduces to returning 'n'.
         */

        return n;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    int n1        = 4;
    int expected1 = 4;
    int output1;

    int n2        = 5;
    int expected2 = 5;
    int output2;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.gcdOfOddEvenSums(n1); });
    double t2 = timeIt([&]() { output2 = s.gcdOfOddEvenSums(n2); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);

    return 0;
}