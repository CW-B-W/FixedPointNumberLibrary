.PHONY: help
help:
	@printf 'usage: make <option>\n'
	@printf '\n'
	@printf 'options:\n'
	@printf '\ttest\t\trun test\n'
	@printf '\tdemo\t\trun demo\n'
	@printf '\tclean\t\tclean compiled files\n'

CC        = g++
CXXFLAGS  = -Wall -O0 --std=c++17
TEST_DEPS = src/FixedPointNumberTest.cpp include/FixedPointNumber.hpp
TEST_SRCS = src/FixedPointNumberTest.cpp
DEMO_DEPS = src/FixedPointNumberDemo.cpp include/FixedPointNumber.hpp
DEMO_SRCS = src/FixedPointNumberDemo.cpp
INCLUDES  = -I./include

.PHONY: test
test: bin/FixedPointNumberTest.out
	bin/FixedPointNumberTest.out

bin/FixedPointNumberTest.out: $(TEST_DEPS)
	$(CC) -o $@ $(TEST_SRCS) $(INCLUDES) $(CXXFLAGS)

.PHONY: demo
demo: bin/FixedPointNumberDemo.out
	bin/FixedPointNumberDemo.out data/

bin/FixedPointNumberDemo.out: $(DEMO_DEPS)
	$(CC) -o $@ $(DEMO_SRCS) $(INCLUDES) $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f bin/*.out
