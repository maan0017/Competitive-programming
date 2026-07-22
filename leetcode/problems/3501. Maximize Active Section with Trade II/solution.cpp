#include "../displayOutputs.h"
#include <bits/stdc++.h> // includes almost everything (works with g++)

class SegmentTree
{
    std::vector<int> st;
    int              n;

    void build(int node, int l, int r, const std::vector<int>& arr)
    {
        if (l == r)
        {
            st[node] = arr[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(2 * node + 1, l, mid, arr);
        build(2 * node + 2, mid + 1, r, arr);
        st[node] = std::max(st[2 * node + 1], st[2 * node + 2]);
    }

    int query(int node, int l, int r, int ql, int qr)
    {
        // Complete overlap
        if (ql <= l && r <= qr)
            return st[node];
        // No overlap
        if (r < ql || l > qr)
            return 0;

        // Partial overlap
        int mid = l + (r - l) / 2;
        return std::max(query(2 * node + 1, l, mid, ql, qr),
                        query(2 * node + 2, mid + 1, r, ql, qr));
    }

  public:
    SegmentTree() : n(0) {}

    SegmentTree(const std::vector<int>& arr)
    {
        n = arr.size();
        if (n > 0)
        {
            st.assign(4 * n, 0);
            build(0, 0, n - 1, arr);
        }
    }

    int query(int l, int r)
    {
        if (n == 0 || l > r)
            return 0;
        return query(0, 0, n - 1, l, r);
    }
};

class Solution
{
  public:
    std::vector<int> maxActiveSectionsAfterTrade(std::string                    s,
                                                 std::vector<std::vector<int>>& queries)
    {
        int n = s.length();

        // The total number of 1s in the entire string
        int activeCount = std::count(s.begin(), s.end(), '1');

        std::vector<int> blockStart;
        std::vector<int> blockEnd;
        std::vector<int> blockSize;

        for (int i = 0; i < n;)
        {
            if (s[i] == '0')
            {
                int start = i;
                while (i < n && s[i] == '0')
                    i++;
                blockStart.push_back(start);
                blockEnd.push_back(i - 1);
                blockSize.push_back(i - start);
            }
            else
            {
                i++;
            }
        }

        int m = blockStart.size();

        std::vector<int> pairSum;
        if (m >= 2)
        {
            pairSum.reserve(m - 1);
            for (int i = 0; i < m - 1; i++)
            {
                pairSum.push_back(blockSize[i] + blockSize[i + 1]);
            }
        }

        SegmentTree      seg(pairSum);
        std::vector<int> result;
        result.reserve(queries.size());

        for (const auto& q : queries)
        {
            int l = q[0];
            int r = q[1];

            if (m < 2)
            {
                result.push_back(activeCount);
                continue;
            }

            int low = std::lower_bound(blockEnd.begin(), blockEnd.end(), l) - blockEnd.begin();
            int high =
                std::upper_bound(blockStart.begin(), blockStart.end(), r) - blockStart.begin() - 1;

            if (low >= high || low >= m || high < 0)
            {
                result.push_back(activeCount);
            }
            else
            {
                int firstLen = blockEnd[low] - std::max(blockStart[low], l) + 1;
                int lastLen  = std::min(blockEnd[high], r) - blockStart[high] + 1;

                if (high - low == 1)
                {
                    result.push_back(activeCount + firstLen + lastLen);
                }
                else
                {
                    int pair1      = firstLen + blockSize[low + 1];
                    int pair2      = blockSize[high - 1] + lastLen;
                    int maxPairSum = std::max(pair1, pair2);

                    if (high - low >= 3)
                    {
                        int rmqMax = seg.query(low + 1, high - 2);
                        maxPairSum = std::max(maxPairSum, rmqMax);
                    }

                    result.push_back(activeCount + maxPairSum);
                }
            }
        }

        return result;
    }
};
int main()
{
    std::ios::sync_with_stdio(false); // fast IO
    std::cin.tie(nullptr);

    // your test cases here
    std::string                   s1        = "01";
    std::vector<std::vector<int>> queries1  = {{0, 1}};
    std::vector<int>              expected1 = {1};
    std::vector<int>              output1;

    std::string                   s2        = "0100";
    std::vector<std::vector<int>> queries2  = {{0, 3}, {0, 2}, {1, 3}, {2, 3}};
    std::vector<int>              expected2 = {4, 3, 1, 1};
    std::vector<int>              output2;

    std::string                   s3        = "1000100";
    std::vector<std::vector<int>> queries3  = {{1, 5}, {0, 6}, {0, 4}};
    std::vector<int>              expected3 = {6, 7, 2};
    std::vector<int>              output3;

    std::string                   s4        = "01010";
    std::vector<std::vector<int>> queries4  = {{0, 3}, {1, 4}, {1, 3}};
    std::vector<int>              expected4 = {4, 4, 2};
    std::vector<int>              output4;

    Solution s;
    // call that function here ->

    double t1 = timeIt([&]() { output1 = s.maxActiveSectionsAfterTrade(s1, queries1); });
    double t2 = timeIt([&]() { output2 = s.maxActiveSectionsAfterTrade(s2, queries2); });
    double t3 = timeIt([&]() { output3 = s.maxActiveSectionsAfterTrade(s3, queries3); });
    double t4 = timeIt([&]() { output4 = s.maxActiveSectionsAfterTrade(s4, queries4); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);
    displayTestCaseOutput(expected4, output4, t4);

    return 0;
}