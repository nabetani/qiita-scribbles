SOURCES=../deque_vec.cpp
TARGET=deque_vec.exe
OPTS=/O2 /Ot /EHsc /GL /GA /Fe$(TARGET) /I.. /I../.. /std:c++17 /utf-8 /W4 

$(TARGET): $(SOURCES)
	$(CC) $(OPTS) $(EXOPTS) $(SOURCES)

clean:
	del $(TARGET)
