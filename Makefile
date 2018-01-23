main: main.c lab1_IO.c
	gcc -g -Wall -o main main.c lab1_IO.c -lpthread -lm

matrixgen: matrixgen.c
	gcc matrixgen.c -o matrixgen

serialtester: serialtester.c lab1_IO.c
	gcc -g -Wall -o serialtester serialtester.c lab1_IO.c

clean:
	rm -rf tmp main main.o matrixgen matrixgen.o serialtester serialtester.o data_input data_output

zip: lab1_IO.c lab1_IO.h main.c Makefile matrixgen.c readme.md timer.h members
	zip 1436255-H41.zip lab1_IO.c lab1_IO.h main.c Makefile matrixgen.c readme.md timer.h