#include <bits/stdc++.h> // includes almost everything (works with g++)
using namespace std;
#include "../displayOutputs.h"

class Solution
{
  public:
    int minScore(int n, vector<vector<int>>& roads)
    {
        // 1. Build the Adjacency List (The Map)
        // Using n + 1 because the cities are 1-indexed (1 to n)
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto& road : roads)
        {
            int u    = road[0];
            int v    = road[1];
            int dist = road[2];

            adj[u].push_back({v, dist});
            adj[v].push_back({u, dist}); // Graph is bidirectional
        }

        // 2. Initialize Trackers
        int          min_score = INT_MAX;
        vector<bool> visited(n + 1, false);
        queue<int>   q;

        // 3. Start Exploration at City 1
        q.push(1);
        visited[1] = true;

        // 4. BFS Traversal
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            // Check all neighboring cities connected to the current city
            for (auto& edge : adj[curr])
            {
                int next_city = edge.first;
                int road_dist = edge.second;

                // CRUCIAL: Always update the minimum score for EVERY road we see,
                // even if we have already visited the city at the other end.
                min_score = min(min_score, road_dist);

                // If we haven't explored the neighbor yet, add it to the queue
                if (!visited[next_city])
                {
                    visited[next_city] = true;
                    q.push(next_city);
                }
            }
        }

        // 5. Return the lowest road distance found in the connected network
        return min_score;
    }
};

int main()
{
    ios::sync_with_stdio(false); // fast IO
    cin.tie(nullptr);

    // your test cases here
    int                 n1        = 4;
    vector<vector<int>> roads1    = {{1, 2, 9}, {2, 3, 6}, {2, 4, 5}, {1, 4, 7}};
    int                 expected1 = 5;
    int                 output1;

    int                 n2        = 4;
    vector<vector<int>> roads2    = {{1, 2, 2}, {1, 3, 4}, {3, 4, 7}};
    int                 expected2 = 2;
    int                 output2;

    int                 n3     = 36;
    vector<vector<int>> roads3 = {
        {{7, 11, 418},   {13, 23, 287},  {16, 25, 7891}, {15, 7, 9695},  {4, 3, 9569},
         {17, 7, 1809},  {14, 3, 4720},  {14, 4, 6118},  {9, 2, 4290},   {32, 17, 5645},
         {14, 16, 426},  {36, 7, 6721},  {13, 30, 9444}, {3, 25, 4635},  {33, 5, 1669},
         {22, 18, 8910}, {5, 28, 7865},  {13, 10, 9466}, {7, 9, 2457},   {11, 8, 4711},
         {17, 11, 6308}, {7, 34, 3789},  {8, 33, 9659},  {16, 3, 4187},  {16, 20, 3595},
         {23, 10, 6251}, {26, 22, 6180}, {4, 16, 5577},  {26, 7, 5398},  {6, 36, 8671},
         {10, 19, 3028}, {23, 30, 1330}, {19, 13, 8315}, {25, 20, 4740}, {25, 4, 5818},
         {30, 10, 8030}, {30, 19, 7527}, {28, 6, 6804},  {21, 27, 1746}, {18, 9, 5189},
         {7, 27, 6560},  {20, 14, 2450}, {27, 32, 3951}, {2, 21, 3927},  {1, 15, 9283},
         {3, 20, 5428},  {15, 26, 5871}, {19, 23, 4533}, {14, 25, 6992}, {4, 20, 5831}}};
    int expected3 = 418;
    int output3;

    Solution s;
    // call that function here ->
    double t1 = timeIt([&]() { output1 = s.minScore(n1, roads1); });
    double t2 = timeIt([&]() { output2 = s.minScore(n2, roads2); });
    double t3 = timeIt([&]() { output3 = s.minScore(n3, roads3); });

    displayTestCaseOutput(expected1, output1, t1);
    displayTestCaseOutput(expected2, output2, t2);
    displayTestCaseOutput(expected3, output3, t3);

    return 0;
}