#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;

class Solution
{
  public:
    int maxNumberOfBalloons(string text)
    {
        // Stack-allocated raw array initialized to 0.
        // Zero heap-allocation overhead, perfect cache locality.
        int freq[26] = {0};

        // Pass by value (char c) instead of reference
        for (char c : text)
        {
            freq[c - 'a']++;
        }

        // We only care about b, a, l, o, n
        int maxAns = freq['b' - 'a'];
        maxAns     = min(maxAns, freq['a' - 'a']);
        maxAns     = min(maxAns, freq['l' - 'a'] / 2);
        maxAns     = min(maxAns, freq['o' - 'a'] / 2);
        maxAns     = min(maxAns, freq['n' - 'a']);

        return maxAns;
    }
};

// --> someone elses code on leet with 0ms runtime
// class Solution {
// public:
//     int maxNumberOfBalloons(string text) {
//         unordered_map<char, int> freq;
//         for (char c : text) {
//             freq[c]++;
//         }
//         return min(
//             {freq['b'], freq['a'], freq['l'] / 2, freq['o'] / 2, freq['n']});
//     }
// };

// --> my code on leet with around 4-8ms runtime
// class Solution {
// public:
//     int maxNumberOfBalloons(string text) {
//         // frequecny of english alphabets
//         vector<int> freq(26, 0);
//         for (const char& c : text) {
//             freq[c - 'a']++;
//         }

//         // a -> 0
//         int maxAns = freq[0];

//         // b -> 1
//         maxAns = min(maxAns, freq[1]);

//         // l ->
//         maxAns = min(maxAns, freq['l' - 'a'] / 2);

//         // o
//         maxAns = min(maxAns, freq['o' - 'a'] / 2);

//         // n
//         maxAns = min(maxAns, freq['n' - 'a']);

//         return maxAns;
//     }
// };

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here

    Solution s;
    // call that function here ->

    return 0;
}