#ifndef COLOR_H
#define COLOR_H

#include <stdint.h> // Для типов данных uint8_t, uint32_t

// Цвета текста и фона по умолчанию
#define COLOR_RESET "\033[0m"

// Основные цвета ANSI для текста и фона
#define C_BLACK "\033[30m"
#define C_RED "\033[31m"
#define C_GREEN "\033[32m"
#define C_YELLOW "\033[33m"
#define C_BLUE "\033[34m"
#define C_MAGENTA "\033[35m"
#define C_CYAN "\033[36m"
#define C_WHITE "\033[37m"
#define C_ORANGE "\033[38;5;214m"
#define C_PURPLE "\033[38;5;129m"
#define C_PINK "\033[38;5;201m"
#define C_BROWN "\033[38;5;130m"
#define C_LIGHT_GRAY "\033[38;5;250m"
#define C_DARK_GRAY "\033[38;5;240m"

#define BACK_BLACK "\033[40m"
#define BACK_RED "\033[41m"
#define BACK_GREEN "\033[42m"
#define BACK_YELLOW "\033[43m"
#define BACK_BLUE "\033[44m"
#define BACK_MAGENTA "\033[45m"
#define BACK_CYAN "\033[46m"
#define BACK_WHITE "\033[47m"
#define BACK_ORANGE "\033[48;5;214m"
#define BACK_PURPLE "\033[48;5;129m"
#define BACK_PINK "\033[48;5;201m"
#define BACK_BROWN "\033[48;5;130m"
#define BACK_LIGHT_GRAY "\033[48;5;250m"
#define BACK_DARK_GRAY "\033[48;5;240m"

// Дополнительные цвета ANSI для текста и фона
#define C_BRIGHT_BLACK "\033[90m"
#define C_BRIGHT_RED "\033[91m"
#define C_BRIGHT_GREEN "\033[92m"
#define C_BRIGHT_YELLOW "\033[93m"
#define C_BRIGHT_BLUE "\033[94m"
#define C_BRIGHT_MAGENTA "\033[95m"
#define C_BRIGHT_CYAN "\033[96m"
#define C_BRIGHT_WHITE "\033[97m"
#define C_BRIGHT_ORANGE (RGB_COLOR){255, 165, 0} // RGB для оранжевого
#define C_BRIGHT_PURPLE (RGB_COLOR){128, 0, 128} // RGB для пурпурного
#define C_BRIGHT_PINK (RGB_COLOR){255, 192, 203} // RGB для розового
#define C_BRIGHT_BROWN (RGB_COLOR){165, 42, 42} // RGB для коричневого
#define C_BRIGHT_LIGHT_GRAY (RGB_COLOR){211, 211, 211} // RGB для светло-серого
#define C_BRIGHT_DARK_GRAY (RGB_COLOR){169, 169, 169} // RGB для темно-серого

#define BACK_BRIGHT_BLACK "\033[100m"
#define BACK_BRIGHT_RED "\033[101m"
#define BACK_BRIGHT_GREEN "\033[102m"
#define BACK_BRIGHT_YELLOW "\033[103m"
#define BACK_BRIGHT_BLUE "\033[104m"
#define BACK_BRIGHT_MAGENTA "\033[105m"
#define BACK_BRIGHT_CYAN "\033[106m"
#define BACK_BRIGHT_WHITE "\033[107m"
#define BACK_COLOR_ORANGE (RGB_COLOR){255, 165, 0}
#define BACK_COLOR_PURPLE (RGB_COLOR){128, 0, 128}
#define BACK_COLOR_PINK (RGB_COLOR){255, 192, 203}
#define BACK_COLOR_BROWN (RGB_COLOR){165, 42, 42}
#define BACK_COLOR_LIGHT_GRAY (RGB_COLOR){211, 211, 211}
#define BACK_COLOR_DARK_GRAY (RGB_COLOR){169, 169, 169}

// Структуры для хранения информации о цвете
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_COLOR;

typedef struct {
    uint32_t hex;
} HEX_COLOR;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a; // Альфа-канал, обычно игнорируется для терминалов
} RGBA_COLOR;

// Определения цветов с понятными именами
#define TEXT_COLOR_RED       (RGB_COLOR){255, 0, 0}
#define TEXT_COLOR_GREEN     (RGB_COLOR){0, 255, 0}
#define TEXT_COLOR_BLUE      (RGB_COLOR){0, 0, 255}
#define TEXT_COLOR_YELLOW    (RGB_COLOR){255, 255, 0}
#define TEXT_COLOR_MAGENTA   (RGB_COLOR){255, 0, 255}
#define TEXT_COLOR_CYAN      (RGB_COLOR){0, 255, 255}
#define TEXT_COLOR_WHITE     (RGB_COLOR){255, 255, 255}
#define TEXT_COLOR_BLACK     (RGB_COLOR){0, 0, 0}

#define TEXT_COLOR_ORANGE       (RGB_COLOR){255, 165, 0}
#define TEXT_COLOR_PURPLE       (RGB_COLOR){128, 0, 128}
#define TEXT_COLOR_PINK         (RGB_COLOR){255, 192, 203}
#define TEXT_COLOR_BROWN        (RGB_COLOR){165, 42, 42}
#define TEXT_COLOR_LIGHT_GRAY   (RGB_COLOR){211, 211, 211}
#define TEXT_COLOR_DARK_GRAY    (RGB_COLOR){169, 169, 169}

#define TEXT_COLOR_BRIGHT_RED       (RGB_COLOR){255, 102, 102}
#define TEXT_COLOR_BRIGHT_GREEN     (RGB_COLOR){102, 255, 102}
#define TEXT_COLOR_BRIGHT_BLUE      (RGB_COLOR){102, 102, 255}
#define TEXT_COLOR_BRIGHT_YELLOW    (RGB_COLOR){255, 255, 102}
#define TEXT_COLOR_BRIGHT_MAGENTA   (RGB_COLOR){255, 102, 255}
#define TEXT_COLOR_BRIGHT_CYAN      (RGB_COLOR){102, 255, 255}
#define TEXT_COLOR_BRIGHT_WHITE     (RGB_COLOR){255, 255, 255}
#define TEXT_COLOR_BRIGHT_BLACK     (RGB_COLOR){153, 153, 153}

#define BG_COLOR_RED         (RGB_COLOR){255, 0, 0}
#define BG_COLOR_GREEN       (RGB_COLOR){0, 255, 0}
#define BG_COLOR_BLUE        (RGB_COLOR){0, 0, 255}
#define BG_COLOR_YELLOW      (RGB_COLOR){255, 255, 0}
#define BG_COLOR_MAGENTA     (RGB_COLOR){255, 0, 255}
#define BG_COLOR_CYAN        (RGB_COLOR){0, 255, 255}
#define BG_COLOR_WHITE       (RGB_COLOR){255, 255, 255}
#define BG_COLOR_BLACK       (RGB_COLOR){0, 0, 0}

#define BG_COLOR_BRIGHT_RED         (RGB_COLOR){255, 102, 102}
#define BG_COLOR_BRIGHT_GREEN       (RGB_COLOR){102, 255, 102}
#define BG_COLOR_BRIGHT_BLUE        (RGB_COLOR){102, 102, 255}
#define BG_COLOR_BRIGHT_YELLOW      (RGB_COLOR){255, 255, 102}
#define BG_COLOR_BRIGHT_MAGENTA     (RGB_COLOR){255, 102, 255}
#define BG_COLOR_BRIGHT_CYAN        (RGB_COLOR){102, 255, 255}
#define BG_COLOR_BRIGHT_WHITE       (RGB_COLOR){255, 255, 255}
#define BG_COLOR_BRIGHT_BLACK       (RGB_COLOR){153, 153, 153}

#define BG_COLOR_ORANGE         (RGB_COLOR){255, 165, 0}
#define BG_COLOR_PURPLE         (RGB_COLOR){128, 0, 128}
#define BG_COLOR_PINK           (RGB_COLOR){255, 192, 203}
#define BG_COLOR_BROWN          (RGB_COLOR){165, 42, 42}
#define BG_COLOR_LIGHT_GRAY     (RGB_COLOR){211, 211, 211}
#define BG_COLOR_DARK_GRAY      (RGB_COLOR){169, 169, 169}

// Функции для установки цвета текста
void set_text_color(uint8_t r, uint8_t g, uint8_t b);
void set_text_color_hex(uint32_t hex);
void set_text_color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void set_text_color_rgb(RGB_COLOR color);
void set_text_color_hex_struct(HEX_COLOR color);
void set_text_color_rgba_struct(RGBA_COLOR color);

// Функции для установки цвета фона
void set_background_color(uint8_t r, uint8_t g, uint8_t b);
void set_background_color_hex(uint32_t hex);
void set_background_color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void set_background_color_rgb(RGB_COLOR color);
void set_background_color_hex_struct(HEX_COLOR color);
void set_background_color_rgba_struct(RGBA_COLOR color);

// Функции для установки цвета текста и фона одновременно
void set_text_and_background_color(RGB_COLOR text_color, RGB_COLOR background_color);
void set_text_and_background_color_hex(HEX_COLOR text_color, HEX_COLOR background_color);
void set_text_and_background_color_rgba(RGBA_COLOR text_color, RGBA_COLOR background_color);

// Функция для сброса цвета текста и фона
void reset_colors(void);

// Вспомогательные функции для преобразования цветов
uint32_t rgb_to_hex(uint8_t r, uint8_t g, uint8_t b);

#endif
