target := bismuth.exe

bin/%.o : src/%.c bin
	gcc -o $(target) $^ -Iinclude/.

bin:
	mkdir bin

