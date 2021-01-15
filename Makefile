#survey: survey.c
#	@cc -Wall survey.c -o survey


all: main.o record.o
	@g++ main.o record.o -o survey

main.o: main.cpp
	@g++ -c main.cpp

record.o: record.cpp
	@g++ -c record.cpp

clean:
	@rm -rf *.o survey

.PHONY: clean
#survey: main.cpp main.h record.cpp record.h
#	@g++ -Wall main.cpp record.cpp -o survey

