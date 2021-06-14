.PHONY: FixedPointNumberTest
FixedPointNumberTest: bin/FixedPointNumberTest.out

bin/FixedPointNumberTest.out: src/FixedPointNumber.cpp src/FixedPointNumberTest.cpp
	g++ -o $@ $^ --std=c++17 -O3

.PHONY: clean
clean:
	rm bin/*.out
