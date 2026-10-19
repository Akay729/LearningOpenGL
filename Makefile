CXX      = g++

# posso include altre cartelle dopo
INC_DIRS = -I./src/Core/

CXXFLAGS = -std=c++17 -O2 -Iinclude  ${INC_DIRS}

# Decommenta la riga per i warning
# CXXFLAGS += -Wall -Wextra

LIBS     = $(shell pkg-config --libs glfw3) -lGL -ldl 
CFLAGS   = $(shell pkg-config --cflags glfw3)

TARGET   = KayEngine
SOURCES      = src/main.cpp src/glad.c src/Core/Application.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
