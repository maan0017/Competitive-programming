#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;

class Solution
{
  public:
    char processStr(string s, long long k)
    {
        int               n = s.size();
        vector<long long> len(n, 0);
        long long         current_len = 0;

        // 1. Precompute the length of the string at each step
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '*')
            {
                current_len = std::max(0LL, current_len - 1);
            }
            else if (s[i] == '#')
            {
                current_len *= 2;
            }
            else if (s[i] == '%')
            {
                // length doesn't change
            }
            else
            {
                current_len++;
            }
            len[i] = current_len;
        }

        // If k is out of bounds of the final string
        if (k >= len[n - 1])
        {
            return '.';
        }

        // 2. Work backward to find the origin of the k-th character
        for (int i = n - 1; i >= 0; i--)
        {
            long long prev_len = (i > 0) ? len[i - 1] : 0;

            if (s[i] == '*')
            {
                // The character at index k just shifts its relative context,
                // but its absolute position before the '*' was still k.
                continue;
            }
            else if (s[i] == '#')
            {
                if (prev_len > 0)
                {
                    // Maps the duplicated right half back to the original left half
                    k %= prev_len;
                }
            }
            else if (s[i] == '%')
            {
                if (prev_len > 0)
                {
                    // Reverses the index
                    k = prev_len - 1 - k;
                }
            }
            else
            {
                // It's a lowercase letter
                if (k == len[i] - 1)
                {
                    return s[i]; // We found the exact letter that lands at k!
                }
            }
        }

        return '.';
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    string    data1     = "z*#";
    long long k1        = 0;
    char      expected1 = '.';

    string    data2     = "%#*gm#xib";
    long long k2        = 2;
    char      expected2 = 'g';

    string    data3     = "a#b%*";
    long long k3        = 1;
    char      expected3 = 'a';

    Solution s;
    // call that function here ->
    char output1 = s.processStr(data1, k1);
    char output2 = s.processStr(data2, k2);
    char output3 = s.processStr(data3, k3);

    if (expected1 == output1)
        cout << "Test case passed" << endl;
    else
        cout << "Test case failed" << endl;

    if (expected2 == output2)
        cout << "Test case passed" << endl;
    else
        cout << "Test case failed" << endl;

    if (expected3 == output3)
        cout << "Test case passed" << endl;
    else
        cout << "Test case failed" << endl;

    return 0;
}