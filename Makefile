# Имя исполняемого файла
TARGET = simulation_earth.exe

# Компилятор и флаги компиляции
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c18

# Исходные файлы и объектные файлы
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Правило по умолчанию - компиляция и линковка
all: $(TARGET)

# Правило сборки исполняемого файла
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Правило сборки объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка сгенерированных файлов
clean:
	del /Q *.o *.exe

# Очистка и повторная компиляция
rebuild: clean all

# Запуск программы
run: $(TARGET)
	$(TARGET)

# Правило для отладки
debug: CFLAGS += -g
debug: rebuild

# Фиктивная цель, чтобы предотвратить ошибки, если файлы с такими именами существуют
.PHONY: all clean rebuild run debug