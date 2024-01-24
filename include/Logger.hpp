#pragma once

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

namespace cmd {
    #define LOG_BUFFER_SIZE 32U
    extern char log_buffer[LOG_BUFFER_SIZE];

    constexpr size_t offset_msg{sizeof("[00:00:00] [------] #####: ") - 1};

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

    template <typename... T>
    void console_print(const msg_side arg1, const msg_type arg2, fmt::format_string<T...> format, T&&... args) {
        auto [_, s1] = fmt::format_to_n(
            log_buffer,
            offset_msg,
            "[{:%T}] [{}] {}: ",
            fmt::localtime(std::time(nullptr)),
            labels::side[arg1],
            labels::type[arg2]
        );
        auto [out, s2] = fmt::format_to_n(
            log_buffer + s1,
            LOG_BUFFER_SIZE - offset_msg - 2,
            format,
            std::forward<T>(args)...
        );
        *out = '\n'; *(out+1)  = '\0';
        fmt::print("{}", log_buffer);
    }
};