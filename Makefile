CXX := g++
TARGET := main
SRC := main.cpp

CXXFLAGS := -std=c++17 -Wall -Wextra -I/usr/include/opencv4
LDLIBS := -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
