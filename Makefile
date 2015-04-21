test: test.o randomized_select.o kd_tree.o queue.o stack.o
	gcc -o $@ $^
test.o: test.c src/randomized_select.h
	gcc -c $<
randomized_select.o: src/randomized_select.c src/randomized_select.h
	gcc -c $<
kd_tree.o: src/kd_tree.c src/kd_tree.h
	gcc -c $<

queue.o: src/queue.c src/queue.h
	gcc -c $<
stack.o: src/stack.c src/stack.h
	gcc -c $<