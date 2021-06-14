.PHONY: help
help:
	@printf "hi"

.PHONY: FIRFilter
FIRFilter: bin/FIRFilter.out

bin/FIRFilter.out: src/FIRFilter.cpp src/FixedPointNumber.cpp
	g++ -o $@ $^ --std=c++17 -O3 -Wall

.PHONY: FixedPointNumberTest
FixedPointNumberTest: bin/FixedPointNumberTest.out

bin/FixedPointNumberTest.out: src/FixedPointNumber.cpp src/FixedPointNumberTest.cpp
	g++ -o $@ $^ --std=c++17 -O3 -Wall

.PHONY: clean
clean:
	rm bin/*.out
