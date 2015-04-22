src := $(shell ls src/*.c)
objs := $(patsubst src/%c,%o,$(src))

test: test.o $(objs)
	gcc -o $@ $^

test.o: test.c
	gcc -c $<

%.o: src/%.c
	gcc -c $<