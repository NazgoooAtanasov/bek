SRC = ${wildcard src/*.c}
HDR = ${wildcard include/*.h}
OBJ = ${SRC:.c=.o}

CFLAGS = -c

bek: ${OBJ}
	cc -g $^ -o $@

%.o: %.c ${HDR}
	cc ${CFLAGS} -g $< -o $@

clean:
	rm src/*.o bek
