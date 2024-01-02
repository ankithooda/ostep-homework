clean:
	rm -rf bin && rm -f measure_cs
syscall:
	mkdir -p bin && gcc -Wall -Wextra -std=c2x -pedantic -g -o bin/bench_syscall bench_syscall.c
measure_cs:
	mkdir -p bin && gcc -Wall -Wextra -std=c2x -pedantic -g -o bin/measure_cs measure_cs.c
memcheck:
	valgrind --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all bin/measure_cs
