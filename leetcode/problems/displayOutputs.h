#pragma once

#include <chrono>
#include <iostream>

// CUSTOM HEADERS
#include "./terminalShpaes.hpp"
using namespace term;

template <typename T> inline void displayTestCaseOutput(T expected, T output, double durationInMs)
{
    static int testCaseNumber = 1;

    if (output == expected)
        std::cout << "[PASS] Test case " << testCaseNumber++ << " | Time: " << durationInMs
                  << " ms\n";
    else
    {
        std::cout << "[FAIL] Test case " << testCaseNumber++ << "\n"
                  << "       Expected : " << expected << "\n"
                  << "       Got      : " << output << "\n";
    }
}

template <typename T>
inline void displayTestCaseOutput(std::vector<T> expected, std::vector<T> output,
                                  double durationInMs)
{
    static int testCaseNumber;

    if (output == expected)
        std::cout << "[PASS] Test case " << testCaseNumber++ << " | Time: " << durationInMs
                  << " ms\n";
    else
    {
        std::cout << "[FAIL] Test case " << testCaseNumber++ << "\n"
                  << "       Expected : [ ";
        for (const T& x : expected)
        {
            std::cout << x << " ";
        }
        std::cout << " ]\n"
                  << "       Got      : [ ";
        for (const T& x : output)
        {
            std::cout << x << " ";
        }
        std::cout << " ]\n";
    }
}

// Returns elapsed milliseconds and writes the result into `out`.
template <typename Func> double timeIt(Func&& f)
{
    auto t0 = std::chrono::steady_clock::now();
    f();
    auto t1 = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

// Returns elapsed seconds.
template <typename Func> double timeItInSeconds(Func&& f)
{
    auto t0 = std::chrono::steady_clock::now();
    f();
    auto t1 = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(t1 - t0).count();
}

// Returns elapsed minutes.
template <typename Func> double timeItInMinutes(Func&& f)
{
    auto t0 = std::chrono::steady_clock::now();
    f();
    auto t1 = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::ratio<60>>(t1 - t0).count();
}

// Returns elapsed hours.
template <typename Func> double timeItInHours(Func&& f)
{
    auto t0 = std::chrono::steady_clock::now();
    f();
    auto t1 = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::ratio<3600>>(t1 - t0).count();
}

// for matrixes have values only 0 & 1
inline void visualizeMatrix(const std::vector<std::vector<int>>& matrix)
{
    static int matrixNumber = 1;

    std::cout << "\n";
    std::cout << "========== Matrix " << matrixNumber++ << " ==========\n\n";

    for (const auto& row : matrix)
    {
        std::cout << "   ";

        for (int cell : row)
        {
            if (cell)
                std::cout << paint(color::brightWhite, "██");
            else
                std::cout << paint(color::brightBlack, "██");
        }

        std::cout << '\n';
    }

    std::cout << "\n";
}

inline void
visualizeMatrixCustomizable(const std::vector<std::vector<int>>& matrix,
                            const std::string& zero = paint(color::brightBlack, shape::largeBlack),
                            const std::string& one  = paint(color::brightWhite, shape::largeWhite))
{
    for (const auto& row : matrix)
    {
        for (int cell : row)
            std::cout << (cell ? one : zero) << ' ';

        std::cout << '\n';
    }
}