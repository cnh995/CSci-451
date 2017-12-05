default: hw11-ChristianHansen-0 p

hw11-ChristianHansen-0.o: hw11-ChristianHansen-0.c
	gcc -c hw11-ChristianHansen.c -o hw11-ChristianHansen.o

hw11-ChristianHansen-0: hw11-ChristianHansen.o
	gcc hw11-ChristianHansen.o -o hw11-ChristianHansen

p1.o: p.c
	gcc -c p.c -o p.o

p1: p.o
	gcc p.o -o p

clean:
	-rm -f hw11-ChristianHansen.o
	-rm -f hw11-ChristianHansen
	-rm -f p.o
	-rm -f p
	-rm -f hw11.out
