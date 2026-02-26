CC = g++
CFLAGS := -lstdc++ -std=c++17 -Wall -Werror -Wextra -g

EXECUTABLE = test

UNAME = $(shell uname)

OPEN_REPORT :=
LEAKS :=

ifeq ($(UNAME), Linux)
OPEN_REPORT += xdg-open
LEAKS += valgrind --leak-check=full -s -q --track-origins=yes
endif

ifeq ($(UNAME), Darwin)
OPEN_REPORT += open
LEAKS += leaks -atExit --
endif

SOURCE = ./tests/*.cc

all: clean test

clean:
	@rm -rf $(EXECUTABLE)
	@rm -rf a.out
	@rm -rf $(OBJ_LIST_TEST)
	@rm -rf $(OBJ_STACK_TEST)
	@rm -rf *.gcno *.gcda report
	@rm -rf tests.info
	@rm -rf report.info

test:
	@$(CC) $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

gcov_report: clean
	@$(CC) $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) --coverage
	@./$(EXECUTABLE)
	mkdir report
	lcov -t "./test" -o report.info --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_REPORT) ./report/index.html
	rm -rf *.gcno *gcda *.gcov

style:
	clang-format -n --style=google s21_containers.h
	clang-format -n --style=google s21_containersplus.h
	clang-format -n --style=google list/*.h
	clang-format -n --style=google stack/*.h
	clang-format -n --style=google queue/*.h
	clang-format -n --style=google tree/*.h
	clang-format -n --style=google map/*.h
	clang-format -n --style=google set/*.h
	clang-format -n --style=google multiset/*.h
	clang-format -n --style=google array/*.h
	clang-format -n --style=google vector/*.h
	clang-format -n --style=google tests/*.cc
	clang-format -n --style=google tests/*.h

clang_format:
	clang-format -i --style=google s21_containers.h
	clang-format -i --style=google s21_containersplus.h
	clang-format -i --style=google list/*.h
	clang-format -i --style=google stack/*.h
	clang-format -i --style=google queue/*.h
	clang-format -i --style=google tree/*.h
	clang-format -i --style=google map/*.h
	clang-format -i --style=google set/*.h
	clang-format -i --style=google multiset/*.h
	clang-format -i --style=google array/*.h
	clang-format -i --style=google vector/*.h
	clang-format -i --style=google tests/*.cc
	clang-format -i --style=google tests/*.h

leaks_check: test
	@$(LEAKS) ./$(EXECUTABLE)

valgrind_test:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./test 2> test_out.txt
