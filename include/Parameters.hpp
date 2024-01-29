#pragma once

//Habilitar colores en el texto de la terminal.
#define CMD_APPLY_COLORS_TERMINAL


// Tamaño del buffer del mensaje a imprimir (no se toma
// en cuenta el primer formato del mensaje ni colores).
#define CMD_LOG_BUFFER_SIZE 64


// Código RGB de colores.
#ifdef CMD_APPLY_COLORS_TERMINAL
static constexpr char cmd_colors_from[5][13] = {
    //  blue,           green         light_red
    "085;085;255m", "035;209;139m", "089;002;087m",
    // strong_red       swamp
    "172;022;044m", "137;012;218m"
};
static constexpr char cmd_colors_level[4][13] = {
    //  cyan,           gold
    "036;114;200m", "255;215;068m",
    //   red,           orange
    "255;085;085m", "252;170;019m"
};
#endif


// Texto de formato a imprimir en cada mensaje.
static constexpr char cmd_txt_from[5][7] =  { "Client", "Server", "OpenGL", "Vulkan", "SDLlib" };
static constexpr char cmd_txt_level[4][6] = { "INFO ", "WARN ", "ERROR", "DEBUG" };


// Tipos y niveles de mensajes posibles (es necesario
// respetar el orden de estos y crear todas las variaciones
// de estas al momento de agregar nuevos tipos de mensajes).
enum Cmd_Log_Type {
    FROM_CLIENT_INFO,
    FROM_CLIENT_WARN,
    FROM_CLIENT_ERROR,
    FROM_CLIENT_DEBUG,

    FROM_SERVER_INFO,
    FROM_SERVER_WARN,
    FROM_SERVER_ERROR,
    FROM_SERVER_DEBUG,

    FROM_OPENGL_INFO,
    FROM_OPENGL_WARN,
    FROM_OPENGL_ERROR,
    FROM_OPENGL_DEBUG,

    FROM_VULKAN_INFO,
    FROM_VULKAN_WARN,
    FROM_VULKAN_ERROR,
    FROM_VULKAN_DEBUG,

    FROM_SDLLIB_INFO,
    FROM_SDLLIB_WARN,
    FROM_SDLLIB_ERROR,
    FROM_SDLLIB_DEBUG
};