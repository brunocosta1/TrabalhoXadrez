all: main

main: main.c
	@ echo 'Building...'
	gcc ./src/*.c main.c -o main

