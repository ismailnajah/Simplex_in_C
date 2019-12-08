
all: bin/ bin/main.o bin/Matrix.o
	gcc -o "bin/main" "bin/main.o" "bin/Matrix.o"

bin/ :
	[ -d bin ] || mkdir -p bin

bin/main.o: src/main.c
	gcc -c "src/main.c" -o bin/main.o 

bin/Matrix.o: src/Matrix.c
	gcc -c "src/Matrix.c" -o bin/Matrix.o 