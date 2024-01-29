#include "Logger.hpp"

int main(void) {
    printf("Ingrese texto a enviar: ");
    char line[16]; scanf("%15[^\n]", line);

    cmd::log(FROM_SDLLIB_INFO,  line);
    cmd::log(FROM_CLIENT_WARN,  "Mensaje numero 2.");
    cmd::log(FROM_SERVER_ERROR, "Mensaje numero 3.");
    cmd::log(FROM_OPENGL_DEBUG, "Mensaje numero 4.");
    cmd::log(FROM_VULKAN_WARN,  "Mensaje numero 5.");
    cmd::log(FROM_SDLLIB_ERROR, "Mensaje numero 6.");
    cmd::log(FROM_CLIENT_INFO,  "Formato %s, multiples %s.", "variable", "opciones");

    return 0;
}