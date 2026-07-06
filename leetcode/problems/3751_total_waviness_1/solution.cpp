#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
// #include <vector>

// ==========================================
// SOLUTION LOGIC
// ==========================================
class Solution
{
  public:
    int sumOfWaviness(int num1, int num2)
    {
        // --- YOUR CODE HERE ---

        if (num1 < 100 && num2 < 100)
            return 0;

        int totalWavinessCount = 0;

        for (int i = num1; i <= num2; ++i)
        {
            if (i < 100)
                continue;

            std::string str = std::to_string(i);

            for (int i = 1; i <= str.size() - 2; i++)
            {
                int prev = i - 1;
                int next = i + 1;

                bool peak   = (str[i] > str[prev]) && (str[i] > str[next]);
                bool valley = (str[i] < str[prev]) && (str[i] < str[next]);

                if (peak || valley)
                    totalWavinessCount++;
            }
        }

        return totalWavinessCount;
    }

    // Solve a single testcase
    void solve(std::istream& in, std::ostream& out, int testcase)
    {
        int num1, num2;
        if (!(in >> num1 >> num2))
            return;

        out << sumOfWaviness(num1, num2) << "\n";
    }
};

// ==========================================
// LOCAL RUNNER (Excluded in Online Judge)
// ==========================================
#ifndef ONLINE_JUDGE

void run_local()
{
    // Open in binary mode to ensure tellg() and seekg() work correctly on Windows
    std::ifstream in("input.txt", std::ios::binary);
    std::ofstream out("output.txt", std::ios::binary);
    std::ofstream log("logs.txt", std::ios::binary); // Overwrites logs on each run

    auto log_msg = [&](const std::string& msg)
    {
        std::cout << msg << std::endl;
        log << msg << std::endl;
    };

    if (!in.is_open())
    {
        log_msg("[Error] input.txt not found in current directory!");
        return;
    }

    int testcases = 1;
    // IMPORTANT: Uncomment the next line if the first input is the number of testcases
    in >> testcases;

    // Optional: consume the trailing newline after testcases if present
    std::string dummy;
    std::getline(in, dummy);

    Solution solver;

    for (int i = 1; i <= testcases; ++i)
    {
        log_msg("[Test Case " + std::to_string(i) + "] Running...");

        std::streampos    start_pos = in.tellg();
        std::stringstream ss_out;

        auto start_time = std::chrono::high_resolution_clock::now();

        // Use std::promise and thread for TLE protection.
        std::promise<void> p;
        auto               future = p.get_future();

        std::thread t(
            [&](std::promise<void> p)
            {
                try
                {
                    solver.solve(in, ss_out, i);
                }
                catch (const std::exception& e)
                {
                    ss_out << "[Error] Exception: " << e.what();
                }
                catch (...)
                {
                    ss_out << "[Error] Unknown exception";
                }
                p.set_value();
            },
            std::move(p));

        // Wait for 2 seconds (Standard CP Time Limit)
        auto status = future.wait_for(std::chrono::seconds(2));

        auto end_time = std::chrono::high_resolution_clock::now();
        auto time_taken =
            std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

        // Capture what was read as input
        std::streampos end_pos   = in.tellg();
        std::string    input_str = "N/A";
        if (start_pos != std::streampos(-1) && end_pos != std::streampos(-1) && end_pos > start_pos)
        {
            in.seekg(start_pos);
            input_str.resize(end_pos - start_pos);
            in.read(&input_str[0], end_pos - start_pos);
            in.seekg(end_pos);
        }

        // Clean up formatting
        auto trim = [](std::string& s)
        {
            while (!s.empty() && (s.back() == '\n' || s.back() == '\r' || s.back() == ' '))
                s.pop_back();
            while (!s.empty() && (s.front() == '\n' || s.front() == '\r' || s.front() == ' '))
                s.erase(0, 1);
        };
        trim(input_str);

        std::string output_str = ss_out.str();
        trim(output_str);

        if (status == std::future_status::timeout)
        {
            std::string error_msg =
                "[Result] Test Case " + std::to_string(i) + " TLE (Time Limit Exceeded)! (>2000ms)";
            log_msg(error_msg);

            out << "[Test Case " << i << "] (TLE)\n";
            out << "Input:    " << input_str << "\n";
            out << "Output:   " << output_str << " (Partial)\n";
            out << "Expected: N/A\n";
            out << "Time:     >2000ms\n\n";

            t.detach(); // Detach to prevent blocking. Note: stream state might be corrupt for subsequent reads.
            break;
        }
        else
        {
            t.join();
            std::string success_msg = "[Result] Test Case " + std::to_string(i) + " Passed in " +
                                      std::to_string(time_taken) + " ms.";
            log_msg(success_msg);

            out << "[Test Case " << i << "]\n";
            out << "Input:    " << input_str << "\n";
            out << "Output:   " << output_str << "\n";
            out << "Expected: N/A\n";
            out << "Time:     " << time_taken << "ms\n\n";
        }
        log_msg(std::string(40, '-'));
    }

    log_msg("[Info] Output written to output.txt");
    log_msg("[Info] Logs written to logs.txt");
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    run_local();
    return 0;
}
#else
// THIS PART RUNS ON LEETCODE / CODEFORCES
int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Solution solver;
    int      testcases = 1;
    // std::cin >> testcases; // Uncomment if first line is testcase count
    for (int i = 1; i <= testcases; ++i)
    {
        solver.solve(std::cin, std::cout, i);
    }
    return 0;
}
#endif
