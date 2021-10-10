
CLANG_FLAGS = -std=c++17 -Wall

GTEST_FLAGS = -lpthread -lgtest_main -lgtest

# determine Python version, need at least 3.7
PYTHON=python3
ifneq (, $(shell which python3.7))
	PYTHON=python3.7
endif
ifneq (, $(shell which python3.8))
	PYTHON=python3.8
endif

build: BookList_test

test: BookList_test
	./BookList_test

grade: grade.py BookList_test
	${PYTHON} grade.py

BookList_test:  Book.hpp Book.cpp BookList.hpp BookList.cpp BookList_test.cpp
	clang++ ${CLANG_FLAGS} ${GTEST_FLAGS} Book.cpp BookList.cpp BookList_test.cpp -o BookList_test

clean:
	rm -f gtest.xml results.json BookList_test BookList_timing
