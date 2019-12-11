IF NOT EXIST bin mkdir bin
gcc -c "src/main.c" -o bin/main.o -g
gcc -c "src/Matrix.c" -o bin/Matrix.o -g
gcc -c "src/Show.c" -o bin/Show.o -g
gcc -o "bin/main" "bin/main.o" "bin/Matrix.o" "bin/Show.o" -g
