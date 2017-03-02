CC=g++
OPTS=-Wall

main: Patcher.o defines.h main.cpp
	${CC} ${OPTS} -o esr_patcher Patcher.o main.cpp

Patcher.o: Patcher.h Patcher.cpp defines.h
	${CC} ${OPTS} -c Patcher.cpp

clean:
	rm -f *.o esr_patcher
