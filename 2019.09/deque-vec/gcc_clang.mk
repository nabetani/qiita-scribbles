OPTS := -std=c++17 -o deque_vec -O3
SOURCES := ../deque_vec.cpp
TARGET := deque_vec

run : $(TARGET)
	./$(TARGET)

$(TARGET) : $(SOURCES)
	$(CC) $(OPTS) $(EXOPTS) $(SOURCES)

clean:
	-rm -f $(TARGET)
