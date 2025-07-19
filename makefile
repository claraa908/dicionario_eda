# Variáveis do projeto
TARGET = freq
TARGET2 = teste_dict

CXX = g++
CXX_STANDARD = -std=c++20
DEBUG_FLAG = -g

# Flags de compilação
CXX_WARNINGS = -Wall -Wextra -Werror -Wpedantic -Wshadow

# Includes do projeto
PROJECT_INCLUDES = -I. -I./includes -I./src

# Arquivos
SRCS = main.cpp \
		src/UnicodeComparator.cpp

SRCS2 = tests_dictionary/main_test.cpp \
		src/UnicodeComparator.cpp

OS := $(shell uname -s)

ifeq ($(OS), Linux)
	ICU_INCLUDES ?= $(shell pkg-config --cflags icu-uc icu-i18n)
	ICU_LIBS ?= $(shell pkg-config --libs icu-uc icu-i18n)
else
	ICU_INCLUDES = -I"C:/msys64/ucrt64/include"
	ICU_LIBS = -L"C:/msys64/ucrt64/lib" -licuuc -licuin -licudt
endif

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) $(CXX_STANDARD) $(DEBUG_FLAG) $(ICU_INCLUDES) $(ICU_LIBS) $(CXX_WARNINGS) $(PROJECT_INCLUDES)

test: $(TARGET2)

$(TARGET2) : $(SRCS2)
	$(CXX) $(SRCS2) -o $(TARGET2) $(CXX_STANDARD) $(DEBUG_FLAG) $(ICU_INCLUDES) $(ICU_LIBS) $(CXX_WARNINGS) $(PROJECT_INCLUDES)

clean:
	rm -f $(TARGET)
	rm -f $(TARGET2)