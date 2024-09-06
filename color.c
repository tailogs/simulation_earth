#include "color.h"
#include <stdio.h>

// Функции установки цвета текста
void set_text_color(uint8_t r, uint8_t g, uint8_t b) {
    printf("\033[38;2;%d;%d;%d;1m", r, g, b);
}

void set_text_color_hex(uint32_t hex) {
    uint8_t r = (hex >> 16) & 0xFF;
    uint8_t g = (hex >> 8) & 0xFF;
    uint8_t b = hex & 0xFF;
    set_text_color(r, g, b);
}

void set_text_color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    (void)a;
    // Альфа-канал обычно не поддерживается терминалами, поэтому его можно игнорировать.
    set_text_color(r, g, b);
}

void set_text_color_rgb(RGB_COLOR color) {
    set_text_color(color.r, color.g, color.b);
}

void set_text_color_hex_struct(HEX_COLOR color) {
    set_text_color_hex(color.hex);
}

void set_text_color_rgba_struct(RGBA_COLOR color) {
    set_text_color_rgba(color.r, color.g, color.b, color.a);
}

// Функции установки цвета фона
void set_background_color(uint8_t r, uint8_t g, uint8_t b) {
    printf("\033[48;2;%d;%d;%d;1m", r, g, b);
}

void set_background_color_hex(uint32_t hex) {
    uint8_t r = (hex >> 16) & 0xFF;
    uint8_t g = (hex >> 8) & 0xFF;
    uint8_t b = hex & 0xFF;
    set_background_color(r, g, b);
}

void set_background_color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    (void)a;
    set_background_color(r, g, b);
}

void set_background_color_rgb(RGB_COLOR color) {
    set_background_color(color.r, color.g, color.b);
}

void set_background_color_hex_struct(HEX_COLOR color) {
    set_background_color_hex(color.hex);
}

void set_background_color_rgba_struct(RGBA_COLOR color) {
    set_background_color_rgba(color.r, color.g, color.b, color.a);
}

// Функции установки цвета текста и фона одновременно
void set_text_and_background_color(RGB_COLOR text_color, RGB_COLOR background_color) {
    set_text_color_rgb(text_color);
    set_background_color_rgb(background_color);
}

void set_text_and_background_color_hex(HEX_COLOR text_color, HEX_COLOR background_color) {
    set_text_color_hex_struct(text_color);
    set_background_color_hex_struct(background_color);
}

void set_text_and_background_color_rgba(RGBA_COLOR text_color, RGBA_COLOR background_color) {
    set_text_color_rgba_struct(text_color);
    set_background_color_rgba_struct(background_color);
}

// Сброс цвета текста и фона
void reset_colors(void) {
    printf("%s", COLOR_RESET);
}

// Преобразование RGB в HEX
uint32_t rgb_to_hex(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 16) | (g << 8) | b;
}
