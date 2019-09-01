CC=clang++
EXOPTS=-mtune=native -mavx -msse4.2 -m32
TARGET=deque_vec.exe

OPTS=-std=c++17 -o $(TARGET) -O3
SOURCES=../deque_vec.cpp

run : $(TARGET)
	$(TARGET)

$(TARGET) : $(SOURCES)
	$(CC) $(OPTS) $(EXOPTS) $(SOURCES)

clean:
	del $(TARGET)

