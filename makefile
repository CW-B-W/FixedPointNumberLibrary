.PHONY: help
help:
	@printf 'usage: make <option>\n'
	@printf '\n'
	@printf 'options:\n'
	@printf '\ttest\t\trun test\n'
	@printf '\tclean\t\tclean compiled files\n'

CC       = g++
CXXFLAGS = -Wall -O3 --std=c++17
DEPS     = src/FixedPointNumberTest.cpp include/FixedPointNumber.hpp
SRCS     = src/FixedPointNumberTest.cpp
INCLUDES = -I./include

.PHONY: test
test: bin/FixedPointNumberTest.out
	bin/FixedPointNumberTest.out

bin/FixedPointNumberTest.out: $(DEPS)
	$(CC) -o $@ $(SRCS) $(INCLUDES) $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f bin/*.out
