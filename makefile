CC=g++
FILES=main.cxx
TARGET=imgorg
$(TARGET):$(FILES)
	$(CC) $(FILES) -o $(TARGET) -Wall -Werror -pedantic -std=c++11
debug:
	$(CC) $(FILES) -o $(TARGET) -Wall -Werror -pedantic -std=c++11 -g

