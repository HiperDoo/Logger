#include "Logger.hpp"

int main(void) {
    printf("Ingrese texto a enviar: ");
    char line[16]; scanf("%15[^\n]", line);

    cmd::console_print(Calling_From::server, Message_Level::info, line);

    cmd::console_print(Calling_From::client, Message_Level::warn,
        "Mensaje numero 2."
    );
    cmd::console_print(Calling_From::client, Message_Level::error,
        "Mensaje numero 3."
    );
    cmd::console_print(Calling_From::opengl, Message_Level::debug,
        "Mensaje numero 4."
    );
    cmd::console_print(Calling_From::server, Message_Level::info,
        "Formato %s, multiples %s.",
        "variable", "opciones"
    );

    return 0;
}