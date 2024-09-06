#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include "color.h"

#define NUM_SYMBOLS 10

typedef struct {
    char name[20];
    int economy;      // Экономика
    int military;     // Военная мощь
    int population;   // Население
    double currencyRate; // Курс валюты
    char currencySymbol; // Символ валюты
    bool isAlive; // новое поле для отслеживания состояния страны
    char symbol;
} CountryData;

// Названия стран
const char names[NUM_SYMBOLS][20] = {
    "Arlandia", "Bravia", "Celestia", "Duran", "Eldoria",
    "Falandia", "Gondor", "Hyrule", "Ithaca", "Jovian"
};

const char currencySymbols[NUM_SYMBOLS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
double currencyHistory[NUM_SYMBOLS][10]; // Хранение истории курсов за последние 10 итераций
bool DEBUG = false;

// Глобальный массив цветов, привязанных к символам
const RGB_COLOR symbolColors[NUM_SYMBOLS] = {
    TEXT_COLOR_RED,            // Символ 0
    TEXT_COLOR_GREEN,          // Символ 1
    TEXT_COLOR_BLUE,           // Символ 2
    TEXT_COLOR_YELLOW,         // Символ 3
    TEXT_COLOR_MAGENTA,        // Символ 4
    TEXT_COLOR_CYAN,           // Символ 5
    TEXT_COLOR_ORANGE,         // Символ 6
    TEXT_COLOR_BRIGHT_BLUE,    // Символ 7
    TEXT_COLOR_BRIGHT_RED,     // Символ 8
    TEXT_COLOR_BRIGHT_GREEN    // Символ 9
};

typedef struct {
    double weights[4]; // Для упрощения, 4 входных веса
    double bias;
} SimpleNN;

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

void initializeNN(SimpleNN *nn) {
    for (int i = 0; i < 4; i++) {
        nn->weights[i] = (rand() % 100) / 100.0;
    }
    nn->bias = (rand() % 100) / 100.0;
}

double predict(SimpleNN *nn, double inputs[4]) {
    double sum = nn->bias;
    for (int i = 0; i < 4; i++) {
        sum += nn->weights[i] * inputs[i];
    }
    return sigmoid(sum);
}

// Функция для скрытия курсора
void hideCursor(HANDLE hConsole) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Скрыть курсор
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// Функция для показа курсора
void showCursor(HANDLE hConsole) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE; // Показать курсор
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// Функция для установки позиции курсора в консоли
void setCursorPosition(HANDLE hConsole, COORD coord) {
    SetConsoleCursorPosition(hConsole, coord);
}

// Функция для сохранения текущей позиции курсора
void saveCursorPosition(HANDLE hConsole, COORD *coord) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    *coord = csbi.dwCursorPosition;
}

// Функция для восстановления сохраненной позиции курсора
void restoreCursorPosition(HANDLE hConsole, COORD coord) {
    SetConsoleCursorPosition(hConsole, coord);
}

void displayNN(SimpleNN *nn, double inputs[4], double output, HANDLE hConsole, COORD *coord) {
    // Устанавливаем курсор на начало области для отображения нейронной сети
    coord->X = 0;
    coord->Y = 22;  // Предположим, что область начинается с 22 строки
    SetConsoleCursorPosition(hConsole, *coord);

    // Очистка старой строки
    set_text_color_rgb(TEXT_COLOR_BLACK);
    printf("Neural Network Visualization:\n");
    reset_colors();

    // Отображаем входные данные
    set_text_color_rgb(TEXT_COLOR_BRIGHT_BLUE);
    printf("Inputs:\n");
    reset_colors();
    for (int i = 0; i < 4; i++) {
        printf("  Input %d: %7.2f\n", i + 1, inputs[i]);
    }

    // Отображаем веса и смещение
    set_text_color_rgb(TEXT_COLOR_GREEN);
    printf("\nWeights and Bias:\n");
    reset_colors();
    for (int i = 0; i < 4; i++) {
        printf("  Weight %d: %7.2f\n", i + 1, nn->weights[i]);
    }
    printf("  Bias: %7.2f\n", nn->bias);

    // Отображаем выходное значение
    set_text_color_rgb(TEXT_COLOR_RED);
    printf("\nOutput of Neural Network: %7.2f\n", output);
    reset_colors();
}

void displayNNTable(SimpleNN *nn, double inputs[4], double output, HANDLE hConsole, COORD *coord) {
    // Устанавливаем курсор на начало области для отображения таблицы
    coord->X = 0;
    coord->Y = 30;  // Предположим, что область начинается с 30 строки
    SetConsoleCursorPosition(hConsole, *coord);

    // Очистка старой строки
    set_text_color_rgb(TEXT_COLOR_WHITE);
    printf("Neural Network Data (Tabular Format):\n");
    reset_colors();
    printf("---------------------------------------------------------------\n");
    printf("| %-7s | %-7s | %-16s | %-10s |\n", "Input", "Weight", "Input * Weight", "Output");
    printf("---------------------------------------------------------------\n");

    double weightedSum = nn->bias;
    set_text_color_rgb(TEXT_COLOR_CYAN);
    for (int i = 0; i < 4; i++) {
        double product = inputs[i] * nn->weights[i];
        weightedSum += product;
        printf("| %7.2f | %7.2f | %16.2f | %10.2f |\n", inputs[i], nn->weights[i], product, weightedSum);
    }
    printf("---------------------------------------------------------------\n");
    reset_colors();
    set_text_color_rgb(TEXT_COLOR_YELLOW);
    printf("Bias: %7.2f\n", nn->bias);
    printf("Output: %7.2f\n", sigmoid(weightedSum));
    reset_colors();
}

void displayNNGraph(SimpleNN *nn, double inputs[4], HANDLE hConsole, COORD *coord) {
    // Устанавливаем курсор на начало области для отображения графа
    coord->X = 0;
    coord->Y = 40;  // Предположим, что область начинается с 40 строки
    SetConsoleCursorPosition(hConsole, *coord);

    // Очистка старой строки
    set_text_color_rgb(TEXT_COLOR_WHITE);
    printf("Neural Network Graph:\n");
    reset_colors();

    // Отображаем входные данные и веса
    set_text_color_rgb(TEXT_COLOR_CYAN);
    printf(" Inputs ");
    reset_colors();
    printf(" --(Weights)--> [Neuron] --(Output)--> [Output]\n");

    // Выводим входы и связи
    for (int i = 0; i < 4; i++) {
        set_text_color_rgb(TEXT_COLOR_BRIGHT_BLUE);
        printf("  [Input%d]", i + 1);
        reset_colors();
        if (i < 3) {
            set_text_color_rgb(TEXT_COLOR_GREEN);
            printf(" --%.2f--> ", nn->weights[i]);
            reset_colors();
        } else {
            printf(" ");
        }
    }
    set_text_color_rgb(TEXT_COLOR_BRIGHT_CYAN);
    printf("--(Bias %.2f)--> [Neuron]\n", nn->bias);
    reset_colors();

    printf("                \\ \n");
    printf("                 \\ \n");

    // Выводим выходной нейрон и его значение
    set_text_color_rgb(TEXT_COLOR_RED);
    printf("                  [Neuron] --%.2f--> [Output]\n", nn->weights[0]); // Только первый вес для примера
    reset_colors();

    // Дополнительная информация о вычислениях
    double weightedSum = nn->bias;
    printf("\n    Calculation Details:\n");
    printf("    Weighted Sum = ");
    set_text_color_rgb(TEXT_COLOR_YELLOW);
    printf("(%7.2f + ", inputs[0] * nn->weights[0]);
    reset_colors();
    for (int i = 1; i < 4; i++) {
        set_text_color_rgb(TEXT_COLOR_YELLOW);
        printf("%7.2f + ", inputs[i] * nn->weights[i]);
        reset_colors();
    }
    set_text_color_rgb(TEXT_COLOR_YELLOW);
    printf("%7.2f) + %.2f = ", sigmoid(nn->bias), nn->bias);
    reset_colors();
    weightedSum += nn->weights[0] * inputs[0] + nn->weights[1] * inputs[1] + nn->weights[2] * inputs[2] + nn->weights[3] * inputs[3];
    printf("%.2f\n", sigmoid(weightedSum));

    printf("    Output = sigmoid(Weighted Sum)\n");
}

void applyNN(SimpleNN *nn, CountryData *countryData, char map[20][60], HANDLE hConsole) {
    if (!countryData->isAlive) return; // Если страна мертва, не применять изменения

    double inputs[4] = {
        countryData->economy,
        countryData->military,
        countryData->population,
        0 // Здесь можно добавить значение для дополнительного контекста, например, среднее значение соседей
    };

    double output = predict(nn, inputs);

    // Создаем координаты для управления курсором
    COORD coord;
    
    // Вывод графических и табличных данных нейросети
    displayNN(nn, inputs, output, hConsole, &coord);
    displayNNTable(nn, inputs, output, hConsole, &coord);
    displayNNGraph(nn, inputs, hConsole, &coord);

    // Применение решения на основе вывода NN
    if (output > 0.5) {
        // Улучшение экономики или населения
        countryData->economy += rand() % 10;
        countryData->military += rand() % 10;
        countryData->population += rand() % 100;
    } else {
        // Уменьшение экономики или населения
        countryData->economy -= rand() % 10;
        countryData->military -= rand() % 10;
        countryData->population -= rand() % 100;

        // Ограничение значений
        if (countryData->economy < 0) countryData->economy = 0;
        if (countryData->military < 0) countryData->military = 0;
        if (countryData->population < 0) countryData->population = 0;
    }

    // Если у страны все основные показатели упали до нуля, то страна считается мертвой
    if (countryData->economy == 0 && countryData->military == 0 && countryData->population == 0) {
        handleCountryDeath(countryData);
    }
}

void handleCountryDeath(CountryData *country) {
    country->isAlive = false;
    country->economy = 0;
    country->military = 0;
    country->population = 0;
    country->currencyRate = 0;
}

// Функция для получения текущего времени в строковом формате
void getCurrentTime(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Функция для записи строки в файл с временной меткой и уровнем
void logToFile(const char *level, const char *logMessage) {
    if (!DEBUG) {
        return;
    }
    const char* filename = "game_log.txt";
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Не удалось открыть файл для логирования");
        return;
    }

    char timestamp[20];
    getCurrentTime(timestamp, sizeof(timestamp));
    
    fprintf(file, "[%s] [%s] %s\n", timestamp, level, logMessage);
    fclose(file);
}

void initializeEmptyCity(CountryData *country) {
    country->economy = 0;
    country->military = 0;
    country->population = 0;
}

void attractPopulation(CountryData *countryData, char map[20][60]) {
    for (int i = 0; i < NUM_SYMBOLS; i++) {
        if (!countryData[i].isAlive) continue; // Если страна мертва, она не привлекает население

        int row, col;
        // Найти текущее положение символа
        for (row = 0; row < 20; row++) {
            for (col = 0; col < 60; col++) {
                if (map[row][col] == 'A' + i) break;
            }
            if (col < 60) break;
        }

        // Если страна пустая, привлекаем население
        if (countryData[i].population == 0) {
            for (int r = row - 1; r <= row + 1; r++) {
                for (int c = col - 1; c <= col + 1; c++) {
                    if (r >= 0 && r < 20 && c >= 0 && c < 60 && map[r][c] != ' ' && map[r][c] != 'A' + i) {
                        int j;
                        for (j = 0; j < NUM_SYMBOLS; j++) {
                            if (map[r][c] == 'A' + j) break;
                        }

                        if (j < NUM_SYMBOLS && countryData[j].isAlive) {
                            countryData[i].population += countryData[j].population / 10;
                            countryData[j].population -= countryData[j].population / 10;
                        }
                    }
                }
            }
        }
    }
}

void updateCurrencyRates(CountryData countryData[NUM_SYMBOLS], int currentRound) {
    for (int i = 0; i < NUM_SYMBOLS; i++) {
        if (!countryData[i].isAlive) continue; // Если страна мертва, не обновлять курс валюты

        // Сохраняем текущий курс в историю
        currencyHistory[i][currentRound % 10] = countryData[i].currencyRate;

        // Обновляем курс валюты, учитывая инфляцию и изменения на рынке
        countryData[i].currencyRate += (rand() % 20 - 10) / 100.0;
        if (countryData[i].currencyRate < 0.5) countryData[i].currencyRate = 0.5; // Минимальный курс
        if (countryData[i].currencyRate > 2.0) countryData[i].currencyRate = 2.0; // Максимальный курс
    }
}

void trade(CountryData *a, CountryData *b) {
    if (!a->isAlive || !b->isAlive) return; // Если одна из стран мертва, торговля не происходит

    double tradeFactor = (a->currencyRate + b->currencyRate) / 2.0;
    int tradeAmount = (rand() % 10 + 1) * tradeFactor; // Объем торговли с учетом курса валют

    // Обмен экономики на военную мощь
    if (a->economy > b->economy) {
        a->military += tradeAmount;
        b->economy += tradeAmount;
    } else {
        b->military += tradeAmount;
        a->economy += tradeAmount;
    }

    // Изменение населения в результате торговли
    int populationChange = (rand() % 100 + 50) * tradeFactor;
    a->population += populationChange;
    b->population -= populationChange;
}

void setMap(char map[20][60], CountryData countryData[NUM_SYMBOLS]) {
    char symbols[NUM_SYMBOLS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int count = 0;

    // Инициализируем карту и данные о странах
    while (count < NUM_SYMBOLS) {
        int row = rand() % 20;
        int col = rand() % 60;

        if (map[row][col] == ' ') {
            map[row][col] = symbols[count];
            countryData[count].economy = rand() % 100 + 1;
            countryData[count].military = rand() % 100 + 1;
            countryData[count].population = rand() % 10000 + 1000;
            countryData[count].currencyRate = (double)(rand() % 100) / 100 + 1; // Начальный курс валюты
            countryData[count].currencySymbol = currencySymbols[count]; // Назначение символа валюты
            strcpy(countryData[count].name, names[count]);
            count++;
        }
    }
}

void countSymbols(char map[20][60], int counts[NUM_SYMBOLS]) {
    char symbols[NUM_SYMBOLS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    for (int i = 0; i < NUM_SYMBOLS; i++) {
        counts[i] = 0;
    }

    // Подсчет вхождений каждого символа
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 60; j++) {
            for (int k = 0; k < NUM_SYMBOLS; k++) {
                if (map[i][j] == symbols[k]) {
                    counts[k]++;
                }
            }
        }
    }
}

void drawMap(char map[20][60], HANDLE hConsole, COORD *coord) {
    DWORD written;

    // Установить курсор в начало консоли
    coord->X = 0;
    coord->Y = 0;
    SetConsoleCursorPosition(hConsole, *coord);

    // Рисуем верхнюю границу карты
    set_text_color_rgb(TEXT_COLOR_BRIGHT_GREEN);
    for (int i = 0; i < 62; i++) {
        putchar('-');
    }
    putchar('\n');
    reset_colors(); // Сброс цвета после границы

    // Вывод карты с боковыми границами
    for (int i = 0; i < 20; i++) {
        putchar('|');
        for (int j = 0; j < 60; j++) {
            char symbol = map[i][j];
            int colorIndex = symbol - 'A'; // Получаем индекс цвета

            if (colorIndex >= 0 && colorIndex < NUM_SYMBOLS) {
                set_text_color_rgb(symbolColors[colorIndex]);
            } else {
                set_text_color_rgb(TEXT_COLOR_WHITE); // Цвет по умолчанию
            }

            putchar(symbol);
            reset_colors(); // Сброс цвета после каждого символа
        }
        putchar('|');
        putchar('\n');
    }

    // Рисуем нижнюю границу карты
    set_text_color_rgb(TEXT_COLOR_BRIGHT_GREEN);
    for (int i = 0; i < 62; i++) {
        putchar('-');
    }
    putchar('\n');
    reset_colors(); // Сброс цвета после границы
}

void drawSymbolInfo(CountryData countryData[NUM_SYMBOLS], int counts[NUM_SYMBOLS], HANDLE hConsole, COORD *coord, int currentRound) {
    DWORD written;

    // Установить курсор для информации справа от карты
    coord->X = 65; // Позиция X для информации справа от карты
    coord->Y = 0;  // Начало с первой строки
    SetConsoleCursorPosition(hConsole, *coord);

    // Вывод информации о символах
    set_text_color_rgb(TEXT_COLOR_BRIGHT_CYAN);
    printf("=============================================|     Symbol Info     |==============================================\n");
    reset_colors();

    static int oldCounts[NUM_SYMBOLS] = {0};
    static int oldEconomy[NUM_SYMBOLS] = {0};
    static int oldMilitary[NUM_SYMBOLS] = {0};
    static int oldPopulation[NUM_SYMBOLS] = {0};
    static double oldCurrencyRates[NUM_SYMBOLS] = {0.0};

    for (int k = 0; k < NUM_SYMBOLS; k++) {
        coord->Y = k + 1;
        SetConsoleCursorPosition(hConsole, *coord);

        // Очистка старой строки
        set_text_color_rgb(TEXT_COLOR_BLACK);
        printf("%-2c - %-10s: %s", 'A' + k, countryData[k].name, "                                                                                                    "); 
        reset_colors();

        // Перемещаем курсор обратно на начало строки
        SetConsoleCursorPosition(hConsole, *coord);

        if (countryData[k].economy == 0 && countryData[k].military == 0 && countryData[k].population == 0) {
            set_text_color_rgb(TEXT_COLOR_BLACK);
            printf("%-2c - %-10s: %-14s| %-12s| %-12s| %-12s\n", 'A' + k, "Deleted", "            ", "            ", "            ", "            ");
            reset_colors();
            continue;
        }

        set_text_color_rgb(symbolColors[k]);
        printf("%-2c - %-10s: ", 'A' + k, countryData[k].name);

        if (counts[k] > oldCounts[k]) {
            set_text_color_rgb(TEXT_COLOR_BRIGHT_GREEN);
            printf("^ %3d cells   ", counts[k]);
        } else if (counts[k] < oldCounts[k]) {
            set_text_color_rgb(TEXT_COLOR_BRIGHT_RED);
            printf("v %3d cells   ", counts[k]);
        } else {
            set_text_color_rgb(TEXT_COLOR_WHITE);
            printf("  %3d cells   ", counts[k]);
        }
        reset_colors();

        // Экономика
        if (countryData[k].economy > oldEconomy[k]) {
            set_text_color_rgb(TEXT_COLOR_BRIGHT_GREEN);
            printf("| Economy: ^%5d ", countryData[k].economy);
        } else if (countryData[k].economy < oldEconomy[k]) {
            set_text_color_rgb(TEXT_COLOR_BRIGHT_RED);
            printf("| Economy: v%5d ", countryData[k].economy);
        } else {
            set_text_color_rgb(TEXT_COLOR_WHITE);
            printf("| Economy:  %5d ", countryData[k].economy);
        }
        reset_colors();

        // Военная мощь
        if (countryData[k].military > oldMilitary[k]) {
            set_text_color_rgb(TEXT_COLOR_BRIGHT_GREEN);
            printf("| Military: ^%5d ", countryData[k].military);
        } else if (countryData[k].military < oldMilitary[k]) {
            set_text_color_rgb(TEXT_COLOR_BRIGHT_RED);
            printf("| Military: v%5d ", countryData[k].military);
        } else {
            set_text_color_rgb(TEXT_COLOR_WHITE);
            printf("| Military:  %5d ", countryData[k].military);
        }
        reset_colors();

        // Население
        if (countryData[k].population > oldPopulation[k]) {
            set_text_color_rgb(TEXT_COLOR_BRIGHT_GREEN);
            printf("| Population: ^%6d ", countryData[k].population);
        } else if (countryData[k].population < oldPopulation[k]) {
            set_text_color_rgb(TEXT_COLOR_BRIGHT_RED);
            printf("| Population: v%6d ", countryData[k].population);
        } else {
            set_text_color_rgb(TEXT_COLOR_WHITE);
            printf("| Population:  %6d ", countryData[k].population);
        }
        reset_colors();

        // Курс валюты
        if (countryData[k].currencyRate > oldCurrencyRates[k]) {
            set_text_color_rgb(TEXT_COLOR_BRIGHT_GREEN);
            printf("| Currency: ^  (%c) %.2f\n", countryData[k].currencySymbol, countryData[k].currencyRate);
        } else if (countryData[k].currencyRate < oldCurrencyRates[k]) {
            set_text_color_rgb(TEXT_COLOR_BRIGHT_RED);
            printf("| Currency: v  (%c) %.2f\n", countryData[k].currencySymbol, countryData[k].currencyRate);
        } else {
            set_text_color_rgb(TEXT_COLOR_WHITE);
            printf("| Currency:    (%c) %.2f\n", countryData[k].currencySymbol, countryData[k].currencyRate);
        }
        reset_colors();

        //coord->Y = coord->Y + 1;
        SetConsoleCursorPosition(hConsole, *coord);
        set_text_color_rgb(TEXT_COLOR_BRIGHT_CYAN);
        //printf("=======================================================================================\n");
        reset_colors();

        oldCounts[k] = counts[k];
        oldEconomy[k] = countryData[k].economy;
        oldMilitary[k] = countryData[k].military;
        oldPopulation[k] = countryData[k].population;
        oldCurrencyRates[k] = countryData[k].currencyRate;
    }

    // Вывод истории валют
    coord->Y = coord->Y + 1;
    SetConsoleCursorPosition(hConsole, *coord);
    set_text_color_rgb(TEXT_COLOR_BRIGHT_CYAN);
    printf("=============================================|   Currency History   |=============================================\n");
    reset_colors();
    for (int h = 0; h < 10; h++) {
        coord->Y = coord->Y + 1;
        SetConsoleCursorPosition(hConsole, *coord);
        printf("|   ");
        for (int k = 0; k < NUM_SYMBOLS; k++) {
            int index = (currentRound - h + 10) % 10;
            printf("%-6.2f ", currencyHistory[k][index]);  // Форматирование вывода значений истории курсов
        }
        printf("|\n");
    }

    coord->Y = coord->Y + 1;
    SetConsoleCursorPosition(hConsole, *coord);
    set_text_color_rgb(TEXT_COLOR_BRIGHT_CYAN);
    //printf("============================================================================================================\n");
    printf("===========================================================================\n");
    reset_colors();
}

void war(CountryData *a, CountryData *b, char map[20][60]) {
    // Простая модель войны: уменьшаем экономику и военную мощь обеих стран
    int damage = rand() % 10 + 1;
    a->economy -= damage;
    a->military -= damage;
    b->economy -= damage;
    b->military -= damage;

    // Учитываем, что экономика и военная мощь не могут быть отрицательными
    if (a->economy < 0) a->economy = 0;
    if (a->military < 0) a->military = 0;
    if (b->economy < 0) b->economy = 0;
    if (b->military < 0) b->military = 0;

    // Определяем победителя
    if (a->military <= 0) {
        // Страна A проиграла
        for (int i = 0; i < NUM_SYMBOLS; i++) {
            if (strcmp(a->name, names[i]) == 0) {
                // Найти позицию символа на карте
                for (int row = 0; row < 20; row++) {
                    for (int col = 0; col < 60; col++) {
                        if (map[row][col] == 'A' + i) {
                            map[row][col] = ' '; // Удалить символ с карты
                            break;
                        }
                    }
                }
                // Очистить данные о стране
                strcpy(a->name, "");
                a->economy = 0;
                a->military = 0;
                a->population = 0;
                return;
            }
        }
    }

    if (b->military <= 0) {
        // Страна B проиграла
        for (int i = 0; i < NUM_SYMBOLS; i++) {
            if (strcmp(b->name, names[i]) == 0) {
                // Найти позицию символа на карте
                for (int row = 0; row < 20; row++) {
                    for (int col = 0; col < 60; col++) {
                        if (map[row][col] == 'A' + i) {
                            map[row][col] = ' '; // Удалить символ с карты
                            break;
                        }
                    }
                }
                // Очистить данные о стране
                strcpy(b->name, "");
                b->economy = 0;
                b->military = 0;
                b->population = 0;
                return;
            }
        }
    }
}

void redistributeResources(CountryData countryData[NUM_SYMBOLS], int affectedCountryIndex) {
    for (int i = 0; i < NUM_SYMBOLS; i++) {
        if (i == affectedCountryIndex || countryData[i].economy == 0) continue;

        // Перераспределение экономики
        int deltaEconomy = rand() % 6 - 3;
        if (deltaEconomy != 0) {
            countryData[affectedCountryIndex].economy += deltaEconomy;
            countryData[i].economy -= deltaEconomy;

            if (countryData[affectedCountryIndex].economy < 0) countryData[affectedCountryIndex].economy = 0;
            if (countryData[i].economy < 0) countryData[i].economy = 0;
        }

        // Перераспределение военной мощи
        int deltaMilitary = rand() % 6 - 3;
        if (deltaMilitary != 0) {
            countryData[affectedCountryIndex].military += deltaMilitary;
            countryData[i].military -= deltaMilitary;

            if (countryData[affectedCountryIndex].military < 0) countryData[affectedCountryIndex].military = 0;
            if (countryData[i].military < 0) countryData[i].military = 0;
        }

        // Перераспределение населения
        int deltaPopulation = rand() % 300 - 150;
        if (deltaPopulation != 0) {
            countryData[affectedCountryIndex].population += deltaPopulation;
            countryData[i].population -= deltaPopulation;

            if (countryData[affectedCountryIndex].population < 0) countryData[affectedCountryIndex].population = 0;
            if (countryData[i].population < 0) countryData[i].population = 0;
        }
    }
}

void updateMapAndData(char map[20][60], CountryData countryData[NUM_SYMBOLS], int currentRound, HANDLE hConsole) {
    int counts[NUM_SYMBOLS];
    countSymbols(map, counts);

    // Обновляем курсы валют
    updateCurrencyRates(countryData, currentRound);

    // Инициализация пустых городов
    for (int i = 0; i < NUM_SYMBOLS; i++) {
        if (countryData[i].population == 0) {
            initializeEmptyCity(&countryData[i]);
        }
    }

    // Привлечение населения
    attractPopulation(countryData, map);

    // Логируем изменения
    char logMessage[256];
    snprintf(logMessage, sizeof(logMessage), "Round %d: Currency Rates Updated", currentRound);
    logToFile("INFO", logMessage);

    for (int i = 0; i < NUM_SYMBOLS; i++) {
        int row, col;
        // Найти текущее положение символа
        for (row = 0; row < 20; row++) {
            for (col = 0; col < 60; col++) {
                if (map[row][col] == 'A' + i) break;
            }
            if (col < 60) break;
        }

        // Проверка и удаление страны, если нужно
        if (countryData[i].economy <= 0 || countryData[i].military <= 0 || countryData[i].population <= 0) {
            // Удалить страну из карты
            map[row][col] = ' ';
            // Очистить данные о стране
            strcpy(countryData[i].name, "");
            countryData[i].economy = 0;
            countryData[i].military = 0;
            countryData[i].population = 0;
            snprintf(logMessage, sizeof(logMessage), "Round %d: Country %s removed", currentRound, countryData[i].name);
            logToFile("INFO", logMessage);
            continue;
        }

        // Взаимодействие между соседними странами
        for (int r = row - 1; r <= row + 1; r++) {
            for (int c = col - 1; c <= col + 1; c++) {
                if (r >= 0 && r < 20 && c >= 0 && c < 60 && map[r][c] != ' ' && map[r][c] != 'A' + i) {
                    int j;
                    for (j = 0; j < NUM_SYMBOLS; j++) {
                        if (map[r][c] == 'A' + j) break;
                    }

                    if (j < NUM_SYMBOLS) {
                        // С вероятностью 50% торговля или война
                        if (rand() % 2 == 0) {
                            trade(&countryData[i], &countryData[j]);
                            snprintf(logMessage, sizeof(logMessage), "Round %d: Trade between %s and %s", currentRound, countryData[i].name, countryData[j].name);
                        } else {
                            war(&countryData[i], &countryData[j], map);
                            snprintf(logMessage, sizeof(logMessage), "Round %d: War between %s and %s", currentRound, countryData[i].name, countryData[j].name);
                        }
                        logToFile("INFO", logMessage);
                    }
                }
            }
        }

        // Выбор действия для страны
        int action = rand() % 3;

        switch (action) {
            case 0: // Изменение экономики
                countryData[i].economy += rand() % 10 - 5; // Увеличение/уменьшение на случайное значение
                snprintf(logMessage, sizeof(logMessage), "Round %d: Economy of %s changed to %d", currentRound, countryData[i].name, countryData[i].economy);
                break;
            case 1: // Изменение военной мощи
                countryData[i].military += rand() % 10 - 5; // Увеличение/уменьшение на случайное значение
                snprintf(logMessage, sizeof(logMessage), "Round %d: Military of %s changed to %d", currentRound, countryData[i].name, countryData[i].military);
                break;
            case 2: // Изменение населения
                countryData[i].population += rand() % 500 - 250; // Увеличение/уменьшение на случайное значение
                snprintf(logMessage, sizeof(logMessage), "Round %d: Population of %s changed to %d", currentRound, countryData[i].name, countryData[i].population);
                break;
        }
        logToFile("INFO", logMessage);

        // Границы значений
        if (countryData[i].economy < 0) countryData[i].economy = 0;
        if (countryData[i].military < 0) countryData[i].military = 0;
        if (countryData[i].population < 0) countryData[i].population = 0;

        // Возможность создания новых ячеек за деньги
        if (countryData[i].economy >= 50) {
            // Ищем свободное место на карте
            int newRow = row + rand() % 3 - 1;
            int newCol = col + rand() % 3 - 1;
            if (newRow >= 0 && newRow < 20 && newCol >= 0 && newCol < 60 && map[newRow][newCol] == ' ') {
                map[newRow][newCol] = 'A' + i;
                countryData[i].economy -= 50; // Уменьшение экономики за создание новой ячейки
                snprintf(logMessage, sizeof(logMessage), "Round %d: New cell created for %s at (%d, %d)", currentRound, countryData[i].name, newRow, newCol);
                logToFile("INFO", logMessage);
            }
        }
    }

    // Применяем нейронную сеть к каждой стране
    SimpleNN nn;
    initializeNN(&nn);

    for (int i = 0; i < NUM_SYMBOLS; i++) {
        applyNN(&nn, &countryData[i], map, hConsole);
    }

    // Проверяем, остались ли символы страны на карте
    for (int i = 0; i < NUM_SYMBOLS; i++) {
        bool found = false;
        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 60; x++) {
                if (map[y][x] == countryData[i].symbol) {
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        countryData[i].isAlive = found; // Обновляем статус страны
    }
}

int main() {
    srand(time(NULL)); // Инициализируем генератор случайных чисел

    char map[20][60];
    char mapStartEnd[64];
    CountryData countryData[NUM_SYMBOLS];

    memset(map, ' ', sizeof(map));
    memset(mapStartEnd, '-', sizeof(mapStartEnd));
    mapStartEnd[0] = '+';
    mapStartEnd[61] = '+';
    mapStartEnd[62] = '\n';
    mapStartEnd[63] = '\0'; // Завершаем строку нулевым символом 

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли
    hideCursor(hConsole);  // Скрываем курсор при старте программы
    DWORD written; // Переменная для хранения количества записанных символов
    COORD coord = {0, 0}; // Координаты курсора для WriteConsoleOutputCharacter

    setMap(map, countryData);

    system("cls");

    int currentRound = 0; // Инициализация счетчика ходов
    while (true) {
        // Устанавливаем курсор в начало консоли
        SetConsoleCursorPosition(hConsole, coord);

        // Рисуем карту
        drawMap(map, hConsole, &coord);

        // Обновляем карту и данные
        updateMapAndData(map, countryData, currentRound, hConsole);

        // Подсчитываем символы
        int counts[NUM_SYMBOLS];
        countSymbols(map, counts);

        // Рисуем информацию о символах
        drawSymbolInfo(countryData, counts, hConsole, &coord, currentRound);

        currentRound++; // Увеличение счетчика ходов

        // Делаем паузу
        Sleep(1000); // 1 секунда
    }

    // Восстанавливаем курсор перед завершением программы
    showCursor(hConsole);

    return 0;
}
