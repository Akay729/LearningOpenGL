CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Iinclude

# Decommenta la riga per i warning
# CXXFLAGS += -Wall -Wextra

LIBS     = $(shell pkg-config --libs glfw3) -lGL -ldl
CFLAGS   = $(shell pkg-config --cflags glfw3)

TARGET   = KayEngine
SRC      = src/main.cpp src/glad.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
