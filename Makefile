COMPILER = clang
WE_FLAGS = -g -Wall -Wpedantic -Wextra -Werror
H_FLAGS = -Iinclude

.PHONY: run clean test

build/a2: build/a2.o build/matrix.o build/format.o
	$(COMPILER) $(WE_FLAGS) $^ -o $@

build/a2.o: src/a2.c | build
	$(COMPILER) -c $(WE_FLAGS) $(H_FLAGS) $^ -o $@

build/matrix.o: src/matrix.c | build
	$(COMPILER) -c $(WE_FLAGS) $(H_FLAGS) $^ -o $@

build/format.o: src/format.c | build
	$(COMPILER) -c $(WE_FLAGS) $(H_FLAGS) $^ -o $@

run: build/a2
	./$^

build: 
	mkdir -p build

clean:
	rm -rf build

test: build/a2
	./test/output_test.sh

# add sanitized build and test later for catching memory leaks
