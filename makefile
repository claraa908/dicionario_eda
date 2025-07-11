#variáveis
TARGET = freq
CXX = g++
IFLAGS = -I"C:/msys64/ucrt64/include"
LFLAGS = -L"C:/msys64/ucrt64/lib" -licuuc -licuin -licudt
SRCS = main.cpp
TEST_FILE = test_output.txt

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) $(IFLAGS) $(LFLAGS)

clean:
	rm -f $(TARGET)