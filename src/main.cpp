#include "Logger.hpp"

int main(void) {
    char line[16];
    scanf("%15[^\n]", line);

    //cmd::console_print(cmd::server, cmd::info, "Hola {}", "HiperDoo");
    cmd::console_print(cmd::server, cmd::info, line);
    cmd::console_print(cmd::server, cmd::info, "Buenas tardes!");

    return 0;
}