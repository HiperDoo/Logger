#include "Logger.hpp"

int main(void) {
    //char line[16];
    //scanf("%15[^\n]", line);

    cmd::console_print(cmd::server, cmd::info, "Buenas tardes!");
    cmd::console_print(cmd::client, cmd::warn, "Mensaje numero 2.");
    cmd::console_print(cmd::client, cmd::error, "Mensaje numero 3.");
    cmd::console_print(cmd::opengl, cmd::debug, "Mensaje numero 4.");
    cmd::console_print(cmd::server, cmd::info, "Soy %s, numero %d.", "HiperDoo", 14);

    return 0;
}