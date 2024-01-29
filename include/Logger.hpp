#pragma once
#include <cinttypes>
#include <string.h>
#include <locale.h>
#include <time.h>

#include "Parameters.hpp"

namespace cmd {
    #ifdef CMD_APPLY_COLORS_TERMINAL
    // La aplicacion de color requiere de 19 bytes y su reseteo 4 bytes.
    static constexpr uint32_t START_TEXT_COLOR_SIZE = 19U + 19U + 19U + 4U;
    static constexpr uint32_t START_TEXT_SIZE = sizeof("[--:--:--] [------] -----: ") + START_TEXT_COLOR_SIZE - 1U;
    #else
    static constexpr uint32_t START_TEXT_SIZE = sizeof("[00:00:00] [------] #####: ") - 1U;
    #endif

    extern char log_buffer[CMD_LOG_BUFFER_SIZE + START_TEXT_SIZE];

    void log(const Cmd_Log_Type type, const char* msg);

    template <typename T, typename... Args>
    void log(const Cmd_Log_Type type, const char* msg, T&& t, Args... args) {
        time_t now{time(nullptr)};

        #ifdef CMD_APPLY_COLORS_TERMINAL
        strftime(log_buffer + 20U, 9U, "%H:%M:%S", localtime(&now));
        *(log_buffer + 28U) = ']';
        memcpy(log_buffer + 37U, cmd_colors_from[type >> 2], 11U);
        memcpy(log_buffer + 50U, cmd_txt_from[type >> 2], 6U);
        memcpy(log_buffer + 65U, cmd_colors_level[type % 4], 11U);
        memcpy(log_buffer + 77U, cmd_txt_level[type % 4], 5U);
        #else
        strftime(log_buffer, 12U, "[%H:%M:%S]", localtime(&now));
        sprintf(log_buffer + 10U, " [%s] %s: ", cmd_txt_from[type >> 2], cmd_txt_level[type % 4]);
        #endif

        uint32_t length = (uint32_t)snprintf(log_buffer + START_TEXT_SIZE, CMD_LOG_BUFFER_SIZE, msg, t, args...);
        length = ((length < CMD_LOG_BUFFER_SIZE - 1) ? length : CMD_LOG_BUFFER_SIZE - 1) + START_TEXT_SIZE;
        log_buffer[length] = '\n';

        fwrite(log_buffer, 1U, length + 1U, stdout);
    }
};