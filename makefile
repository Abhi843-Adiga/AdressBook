var:=$(patsubst %.c,%.o,$(wildcard *.c))
abhi.exe:$(var)
	gcc -o $@ $^
clean:
	rm *.o *.exe
