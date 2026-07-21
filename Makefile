COMPILER = clang
FLAGS = -g -Wall -Wpedantic -Wextra -Werror

PROG ?= a2
EXE = build/$(PROG)

all: $(EXE)
	@:

%: build/%
	@:

build/%: src/%.c
	mkdir -p build
	$(COMPILER) $(FLAGS) $^ -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -rf build

test: $(EXE)
	./test/output_test.sh

# add sanitized build and test later for catching memory leaks
