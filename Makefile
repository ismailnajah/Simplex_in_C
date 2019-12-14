
all: bin/ bin/main.o bin/Matrix.o bin/Show.o bin/Simplex.o
	gcc -o "bin/main" "bin/main.o" "bin/Simplex.o" "bin/Matrix.o" "bin/Show.o" -g

bin/ :
	[ -d bin ] || mkdir -p bin

bin/main.o: src/main.c
	gcc -c "src/main.c" -o bin/main.o -g

bin/Matrix.o: src/Matrix.c
	gcc -c "src/Matrix.c" -o bin/Matrix.o -g

bin/Show.o: src/Show.c
	gcc -c "src/Show.c" -o bin/Show.o -g

bin/Simplex.o: src/Simplex.c
	gcc -c "src/Simplex.c" -o bin/Simplex.o -g