#include "Logger.hpp"

namespace cmd {
    #ifdef APPLY_COLORS
    char log_buffer[LOG_BUFFER_SIZE + START_TEXT_SIZE] =
        "\033[38;2;112;128;144m[##:##:##] " // rgb(112,128,144) | slate_gray
        "\033[38;2;###########m[------] "
        "\033[38;2;###########m-----"
        "\033[0m: ";
    #else
    char log_buffer[LOG_BUFFER_SIZE + START_TEXT_SIZE];
    #endif

    void console_print(const Calling_From from, const Message_Level level, const char* msg) {
        time_t now{time(nullptr)};

        #ifdef APPLY_COLORS
        strftime(log_buffer + 20U, 9U, "%H:%M:%S", localtime(&now));
        *(log_buffer + 28U) = ']';
        memcpy(log_buffer + 37U, color_from[from], 11U);
        memcpy(log_buffer + 50U, txt_from[from], 6U);
        memcpy(log_buffer + 65U, color_level[level], 11U);
        memcpy(log_buffer + 77U, txt_level[level], 5U);
        #else
        strftime(log_buffer, 12U, "[%H:%M:%S]", localtime(&now));
        sprintf(log_buffer + 10U, " [%s] %s: ", txt_from[from], txt_level[level]);
        #endif

        const size_t length = strnlen(msg, LOG_BUFFER_SIZE - 1);
        strncpy(log_buffer + START_TEXT_SIZE, msg, length);
        log_buffer[length + START_TEXT_SIZE] = '\n';

        fwrite(log_buffer, 1U, START_TEXT_SIZE + length + 1U, stdout);
    }
};