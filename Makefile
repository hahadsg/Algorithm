test: test.o randomized_select.o
	gcc -o $@ $^
test.o: test.c src/randomized_select.h
	gcc -c $<
randomized_select.o: src/randomized_select.c src/randomized_select.h
	gcc -c $<