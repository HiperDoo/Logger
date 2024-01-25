#pragma once

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

#define APPLY_COLORS

namespace cmd {
    #define LOG_BUFFER_SIZE 64U

    #ifdef APPLY_COLORS
    // C=color | R=reset_color                 >C[00:00:00]R C[------]R C#####:R <
    constexpr uint32_t START_TEXT_COLOR_SIZE = (19U + 4U) + (19U + 4U) + (19U + 4U);
    constexpr uint32_t START_TEXT_SIZE = sizeof("[00:00:00] [------] #####: ") + START_TEXT_COLOR_SIZE - 1U;
    constexpr uint32_t START_TEXT_OFFSET = LOG_BUFFER_SIZE - START_TEXT_SIZE - 2;

    extern char log_buffer[LOG_BUFFER_SIZE + START_TEXT_COLOR_SIZE];
    #else
    #define LOG_BUFFER_SIZE 64U
    constexpr size_t offset_msg{sizeof("[00:00:00] [------] #####: ") - 1};
    extern char log_buffer[LOG_BUFFER_SIZE];
    #endif

    namespace labels {
        constexpr char side[3][7] = { "Server", "Client", "OpenGL" };
        constexpr char type[4][6] = { "INFO ", "WARN ", "ERROR", "DEBUG" };
        #ifdef APPLY_COLORS
        constexpr fmt::rgb side_c[3] = {
            {35, 209, 139}, {85, 85, 255}, {89, 2, 87}
        };
        constexpr fmt::rgb type_c[4] = {
            {36, 114, 200}, {255, 215, 68}, {255, 85, 85}, {252, 170, 19}
        };
        #endif
    };
    enum msg_side { server, client, opengl };
    enum msg_type { info, warn, error, debug };

    /*template <typename T, typename... Args>
    void console_print(const msg_side arg1, const msg_type arg2, fmt::format_string<T, Args...> format, T&& t, Args... args) {
        fmt::format_to_n(
            log_buffer,
            offset_msg,
            "[{:%T}] [{}] {}: ",
            fmt::localtime(std::time(nullptr)),
            labels::side[arg1],
            labels::type[arg2]
        );
        auto [out, _] = fmt::format_to_n(
            log_buffer + offset_msg,
            LOG_BUFFER_SIZE - offset_msg - 2,
            format,
            std::forward<T>(t), std::forward<Args>(args)...
        );
        *out = '\n'; *(out+1)  = '\0';

        fmt::print("{}", log_buffer);
    }*/

    void console_print(const msg_side arg1, const msg_type arg2, const char* msg);
};