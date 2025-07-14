# Variáveis do projeto
TARGET = freq
CXX = g++
CXX_STANDARD = -std=c++20
DEBUG_FLAG = -g

# Variáveis da ICU
ICU_INCLUDES = -I"C:/msys64/ucrt64/include"
ICU_LIBS = -L"C:/msys64/ucrt64/lib" -licuuc -licuin -licudt

# Flags de compilação
CXX_WARNINGS = -Wall -Wextra -Werror -Wpedantic -Wshadow

# Includes do projeto
PROJECT_INCLUDES = -I. -I./includes -I./src

# Arquivos
SRCS = main.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) $(CXX_STANDARD) $(DEBUG_FLAG) $(ICU_INCLUDES) $(ICU_LIBS) $(CXX_WARNINGS) $(PROJECT_INCLUDES)

clean:
	rm -f $(TARGET)