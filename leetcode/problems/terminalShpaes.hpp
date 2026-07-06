#pragma once

#include <string>

namespace term
{
    namespace color
    {
        inline constexpr const char* reset = "\033[0m";

        inline constexpr const char* black   = "\033[30m";
        inline constexpr const char* red     = "\033[31m";
        inline constexpr const char* green   = "\033[32m";
        inline constexpr const char* yellow  = "\033[33m";
        inline constexpr const char* blue    = "\033[34m";
        inline constexpr const char* magenta = "\033[35m";
        inline constexpr const char* cyan    = "\033[36m";
        inline constexpr const char* white   = "\033[37m";

        inline constexpr const char* brightBlack   = "\033[90m";
        inline constexpr const char* brightRed     = "\033[91m";
        inline constexpr const char* brightGreen   = "\033[92m";
        inline constexpr const char* brightYellow  = "\033[93m";
        inline constexpr const char* brightBlue    = "\033[94m";
        inline constexpr const char* brightMagenta = "\033[95m";
        inline constexpr const char* brightCyan    = "\033[96m";
        inline constexpr const char* brightWhite   = "\033[97m";
    } // namespace color

    namespace shape
    {
        inline constexpr const char* squareFilled = "■";
        inline constexpr const char* squareEmpty  = "□";

        inline constexpr const char* blockFull   = "█";
        inline constexpr const char* blockDark   = "▓";
        inline constexpr const char* blockMedium = "▒";
        inline constexpr const char* blockLight  = "░";

        inline constexpr const char* largeWhite  = "⬜";
        inline constexpr const char* largeBlack  = "⬛";
        inline constexpr const char* largeBlue   = "🟦";
        inline constexpr const char* largeRed    = "🟥";
        inline constexpr const char* largeGreen  = "🟩";
        inline constexpr const char* largeYellow = "🟨";

        inline constexpr const char* circleFilled = "●";
        inline constexpr const char* circleEmpty  = "○";

        inline constexpr const char* diamondFilled = "◆";
        inline constexpr const char* diamondEmpty  = "◇";

        inline constexpr const char* triangleUp   = "▲";
        inline constexpr const char* triangleDown = "▼";

        inline constexpr const char* star  = "★";
        inline constexpr const char* heart = "♥";
    } // namespace shape

    inline std::string paint(const char* color, const char* symbol)
    {
        return std::string(color) + symbol + color::reset;
    }
} // namespace term