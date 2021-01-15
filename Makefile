#survey: survey.c
#	@cc -Wall survey.c -o survey

survey: main.cpp
	@g++ -Wall main.cpp -o survey

