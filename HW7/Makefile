default: hw7-ChristianHansen

hw7-ChristianHansen.o: hw7-ChristianHansen.c
	gcc -c hw7-ChristianHansen.c -o hw7-ChristianHansen.o -pthread

hw7-ChristianHansen: hw7-ChristianHansen.o
	gcc hw7-ChristianHansen.o -o hw7-ChristianHansen -pthread

clean:
	-rm -f hw7-ChristianHansen.o
	-rm -f hw7-ChristianHansen
	-rm -f hw7.mutex
	-rm -f hw7.nomutex
