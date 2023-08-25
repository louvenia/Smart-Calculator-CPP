CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic

TEST_SRC = $(wildcard tests/*.cc)
MODEL_SRC = s21_SmartCalc_v2/model/*.cc

all: clean test install

test:
	$(CC) --coverage $(CFLAGS) $(TEST_SRC) $(MODEL_SRC) -lgtest -o test
	./test

install:
	mkdir Build
	cmake s21_SmartCalc_v2 -B Build
	cmake --build Build

uninstall:
	cd Build && make clean
	rm -rf Build/CMakeCache.txt Build/s21_SmartCalc_v2.app
	rm -r Build

dist:
	cd .. && tar -czf SRC_CPP3_SmartCalc_v2.tgz src

dist_clean:
	cd .. && rm SRC_CPP3_SmartCalc_v2.tgz

dvi:
	makeinfo manual.texi --html
	open ./manual/index.html

dvi_clean:
	rm -rf manual

check:
	cp ../materials/linters/.clang-format ./
	# clang-format -i tests/*.cc
	# clang-format -i s21_SmartCalc_v2/controller/*.cc s21_SmartCalc_v2/controller/*.h
	# clang-format -i s21_SmartCalc_v2/library/*.cc s21_SmartCalc_v2/library/*.h
	# clang-format -i s21_SmartCalc_v2/model/*.cc s21_SmartCalc_v2/model/*.h
	# clang-format -i s21_SmartCalc_v2/view/*.cc s21_SmartCalc_v2/view/*.h s21_SmartCalc_v2/main.cc
	clang-format -n tests/*.cc
	clang-format -n s21_SmartCalc_v2/controller/*.cc s21_SmartCalc_v2/controller/*.h
	clang-format -n s21_SmartCalc_v2/library/*.cc s21_SmartCalc_v2/library/*.h
	clang-format -n s21_SmartCalc_v2/model/*.cc s21_SmartCalc_v2/model/*.h
	clang-format -n s21_SmartCalc_v2/view/*.cc s21_SmartCalc_v2/view/*.h s21_SmartCalc_v2/main.cc
	rm .clang-format

leaks:
	leaks -atExit -- ./test

gcov_report:
	gcovr -r . --html --html-details -o report.html
	open report.html

clean:
	rm -rf test *.dSYM *.o *.a *.gcda *.gcno *.info *.out *.txt report .clang_format *.css *.html *.gcov manual ../SRC_CPP3_SmartCalc_v2.tgz