#include "Logger.hpp"

int main(void) {
    cmd::console_print(cmd::server, cmd::info, "Hola {}\n", "HiperDoo");

    return 0;
}