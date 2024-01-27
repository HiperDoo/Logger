#pragma once
#include <cinttypes>
#include <string.h>
#include <locale.h>
#include <time.h>

#define APPLY_COLORS

enum Calling_From { server, client, opengl };
enum Message_Level { info, warn, error, debug };

namespace cmd {
    #define LOG_BUFFER_SIZE 64

    #ifdef APPLY_COLORS
    static constexpr char color_from[3][11] = {
        { 48, 51, 53, 59, 50, 48, 57, 59, 49, 51, 57 }, // rgb(35, 209, 139) | green
        { 48, 56, 53, 59, 48, 56, 53, 59, 50, 53, 53 }, // rgb(85, 85, 255)  | blue
        { 48, 56, 57, 59, 48, 48, 50, 59, 48, 56, 55 }  // rgb(89, 2, 87)    | light_red
    };
    static constexpr char color_level[4][11] = {
        { 48, 51, 54, 59, 49, 49, 52, 59, 50, 48, 48 }, // rgb(36, 114, 200) | cyan
        { 50, 53, 53, 59, 50, 49, 53, 59, 48, 54, 56 }, // rgb(255, 215, 68) | gold
        { 50, 53, 53, 59, 48, 56, 53, 59, 48, 56, 53 }, // rgb(255, 85, 85)  | red
        { 50, 53, 50, 59, 49, 55, 48, 59, 48, 49, 57 }  // rgb(252, 170, 19) | orange
    };

    // La aplicacion de color requiere de 19 bytes y su reseteo 4 bytes.
    static constexpr uint32_t START_TEXT_COLOR_SIZE = 19U + 19U + 19U + 4U;
    static constexpr uint32_t START_TEXT_SIZE = sizeof("[--:--:--] [------] -----: ") + START_TEXT_COLOR_SIZE - 1U;
    #else
    static constexpr uint32_t START_TEXT_SIZE = sizeof("[00:00:00] [------] #####: ") - 1U;
    #endif

    extern char log_buffer[LOG_BUFFER_SIZE + START_TEXT_SIZE];

    static constexpr char txt_from[3][7] = { "Server", "Client", "OpenGL" };
    static constexpr char txt_level[4][6] = { "INFO ", "WARN ", "ERROR", "DEBUG" };

    void console_print(const Calling_From from, const Message_Level level, const char* msg);

    template <typename T, typename... Args>
    void console_print(const Calling_From from, const Message_Level level, const char* msg, T&& t, Args... args) {
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

        uint32_t length = (uint32_t)snprintf(log_buffer + START_TEXT_SIZE, LOG_BUFFER_SIZE, msg, t, args...);
        length = ((length < LOG_BUFFER_SIZE - 1) ? length : LOG_BUFFER_SIZE - 1) + START_TEXT_SIZE;
        log_buffer[length] = '\n';

        fwrite(log_buffer, 1U, length + 1U, stdout);
    }
};