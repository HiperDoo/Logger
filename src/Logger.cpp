#include "Logger.hpp"

namespace cmd {
    char log_buffer[LOG_BUFFER_SIZE + START_TEXT_COLOR_SIZE];

    void console_print(const msg_side arg1, const msg_type arg2, const char* msg) {
        #ifdef APPLY_COLORS
        fmt::format_to_n(
            log_buffer,
            START_TEXT_SIZE,
            "{} {} {}: ",
            fmt::format(fg(fmt::color::slate_gray), "[{:%T}]", fmt::localtime(std::time(nullptr))),
            fmt::format(fg(labels::side_c[arg1]), "[{}]", labels::side[arg1]),
            fmt::format(fg(labels::type_c[arg2]), "{}", labels::type[arg2])
        );
        #else
        fmt::format_to_n(
            log_buffer,
            offset_msg,
            "[{:%T}] [{}] {}: ",
            fmt::localtime(std::time(nullptr)),
            labels::side[arg1],
            labels::type[arg2]
        );
        #endif

        const size_t length = strnlen(msg, START_TEXT_OFFSET);
        strncpy(log_buffer + START_TEXT_SIZE, msg, length);
        char* ptr = &log_buffer[length + START_TEXT_SIZE];
        *ptr = '\n'; *(ptr+1) = '\0';

        fmt::print("{}", log_buffer);
    }
};