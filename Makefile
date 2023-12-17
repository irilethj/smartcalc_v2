TEST=test
CFLAGS=-Wall -Werror -Wextra -std=c++17
SRC=Calculator_2/controller/controller.cc Calculator_2/model/model.cc test.cc
GCOV=--coverage
TESTFLAGS=-lgtest -lgcov 
UNAME = $(shell uname -s)
DOC_DIR = doc
DOC_FILE = smartcalc.texi

ifeq ($(UNAME),Linux)
	CC=g++
	QMAKE=qmake6
	PROJECTNAME=Calculator_2
	HTML=lcov -t test -o rep.info -c -d ./
	OPEN=../build/Calculator_2.app
endif
ifeq ($(UNAME),Darwin)
	CC=g++-13
    QMAKE=qmake
	PROJECTNAME=Calculator_2.app
	HTML=lcov --gcov-tool /opt/homebrew/bin/gcov-13 -t test -o rep.info -c -d . --ignore-errors mismatch --exclude /usr --exclude 13
	OPEN=open ../build/Calculator_2.app
endif


all: clean install

test: $(SRC)
	$(CC) $(CFLAGS) $(GCOV) $(SRC) $(TESTFLAGS) -o $(TEST)
	./$(TEST)

gcov_report: test
	$(HTML)
	genhtml -o report rep.info
	open report/index.html

install:
	@rm -rf ../build
	@mkdir ../build
	@cd Calculator_2 && cd view && $(QMAKE) && make && make clean && rm -rf Makefile && mv $(PROJECTNAME) ../../../build/Calculator_2.app
	@echo "Install completed"
	$(OPEN)

uninstall:
	rm -rf ../build
	@echo "Uninstall completed"

dvi:
	cd $(DOC_DIR); $(TEXI2DVI) $(DOC_FILE)
	cd $(DOC_DIR); dvipdfm smartcalc.dvi
	cd $(DOC_DIR); open smartcalc.pdf

dist:
	@mkdir -p ../dist
	@cp -R ../build/Calculator_2.app ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf Calculator_2.tgz *
	@cd ../dist && rm -rf Calculator_2.app README.md README_RUS.md
	@echo "The build was successfully archived"

format:
	clang-format -i -style=Google *.cc Calculator_2/controller/*.cc Calculator_2/controller/*.h 
	clang-format -i -style=Google Calculator_2/model/*.cc Calculator_2/model/*.h
	clang-format -i -style=Google Calculator_2/view/*.cc Calculator_2/view/*.h


leaks: test
	leaks -atExit -- ./$(TEST)

valgrind: clean test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM doc/smartcalc.dvi doc/smartcalc.pdf doc/smartcalc.aux doc/smartcalc.toc doc/smartcalc.log
	 

 # Перечисление целей, которые не являются названиями файлов
.PHONY: all style valgrind install unistall dvi dist test gcov_report clean
