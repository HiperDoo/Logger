#include "Logger.hpp"

namespace cmd {
    #ifdef CMD_APPLY_COLORS_TERMINAL
    char log_buffer[CMD_LOG_BUFFER_SIZE + START_TEXT_SIZE] =
        "\033[38;2;112;128;144m[##:##:##] " // rgb(112,128,144) slate_gray
        "\033[38;2;############[------] "
        "\033[38;2;############-----"
        "\033[0m: ";                        // reset_color
    #else
    char log_buffer[CMD_LOG_BUFFER_SIZE + START_TEXT_SIZE];
    #endif

    void log(const Cmd_Log_Type type, const char* msg) {
        time_t now{time(nullptr)};

        #ifdef CMD_APPLY_COLORS_TERMINAL
        strftime(log_buffer + 20U, 9U, "%H:%M:%S", localtime(&now));
        *(log_buffer + 28U) = ']';
        memcpy(log_buffer + 37U, cmd_colors_from[type >> 2], 12U);
        memcpy(log_buffer + 50U, cmd_txt_from[type >> 2], 6U);
        memcpy(log_buffer + 65U, cmd_colors_level[type % 4], 12U);
        memcpy(log_buffer + 77U, cmd_txt_level[type % 4], 5U);
        #else
        strftime(log_buffer, 12U, "[%H:%M:%S]", localtime(&now));
        sprintf(log_buffer + 10U, " [%s] %s: ", cmd_txt_from[type >> 2], cmd_txt_level[type % 4]);
        #endif

        const size_t length = strnlen(msg, CMD_LOG_BUFFER_SIZE - 1);
        strncpy(log_buffer + START_TEXT_SIZE, msg, length);
        log_buffer[length + START_TEXT_SIZE] = '\n';

        fwrite(log_buffer, 1U, START_TEXT_SIZE + length + 1U, stdout);
    }
};