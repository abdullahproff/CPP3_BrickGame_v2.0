TEST_FLAGS= -lgtest_main -pthread -lgtest
GCC= g++ -Wall -Wextra -Werror -std=c++17
GCO= --coverage

SRC_DIR := .
EXTENSIONS := cc cpp h
# Функция для обнаружения файлов с заданными расширениями в директории и ее поддиректориях
find_files = $(foreach ext,$(EXTENSIONS),$(wildcard $(1)/*.$(ext))) $(foreach d,$(wildcard $(1)/*),$(call find_files,$(d)))
SRC_FILES := $(call find_files,$(SRC_DIR))

# Фильтрация только файлов с расширением .cc
CC_FILES := $(filter-out ./gui/desktop/main.cc ./gui/desktop/SnakeView.cc, $(filter %.cc,$(SRC_FILES)))

RM_RULE= rm -rf main test *.dSYM report res *.info *.gcda *.gcno snake_game

UNAME := $(shell uname -s)

FILES= $(wildcard *.cc)
OBJ=$(patsubst %.cc,%.o,${FILES})

all: install tests dvi run_desktop

install: clean
	mkdir ../build
	cp -rf images ../build
	cd ../build && cmake ../ && make

.PHONY : install

uninstall:
	rm -rf ../build

.PHONY : uninstall

desktop: clean
	mkdir ../build
	cp -rf images ../build
	cd ../build && cmake ../ && make desktopBrickGame && ./desktopBrickGame

.PHONY : desktop

run_desktop:
	cd ../build && ./desktopBrickGame

.PHONY : run_desktop

cli: clean
	mkdir ../build
	cp -rf images ../build
	cd ../build && cmake ../ && make consoleBrickGame

.PHONY : cli

run_cli:
	cd ../build && ./consoleBrickGame

.PHONY : run_cli

tests:
	clear
	$(GCC) $(TEST_FLAGS) -g -o test tests/snake_test.cc tests/tetris_test.cc brick_game/snake/SnakeModel.cc brick_game/tetris/TetrisModel.cc brick_game/tetris/Tetromino.cc
	./test

.PHONY : tests

clean:
	$(RM_RULE)
	rm -rf ../build ../BrickGames ../BrickGames.tgz coverage_report SnakeScore.txt TetrisScore.txt
	make style
	clear

.PHONY : clean

dvi:
	open ../dvi/dvi.pdf

.PHONY : dvi

dist: install
	mkdir -p BrickGames
	touch BrickGames/Makefile
	echo ".PHONY: all dvi \nall: dvi run_desktop\nrun_cli:\n\tcd build && ./consoleBrickGame\n\nrun_desktop:\n\tcd build && ./desktopBrickGame\ndvi:\n\topen dvi/dvi.pdf" >> BrickGames/Makefile
	cp -R ../build ../dvi images BrickGames/
	tar cvzf BrickGames.tgz BrickGames/
	mv BrickGames.tgz ../
	rm -rf BrickGames/

.PHONY : dist

gcov_report: clean
	$(GCC) $(TEST_FLAGS) $(GCO) -o report tests/snake_test.cc tests/tetris_test.cc brick_game/snake/SnakeModel.cc brick_game/tetris/TetrisModel.cc brick_game/tetris/Tetromino.cc
	./report
	gcov tests/snake_test.cc tests/tetris_test.cc brick_game/snake/SnakeModel.cc brick_game/tetris/TetrisModel.cc brick_game/tetris/Tetromino.cc
	lcov --capture --directory . --output-file coverage.info --no-external
	genhtml coverage.info --output-directory coverage_report
ifeq ($(UNAME), Linux)
	google-chrome ./coverage_report/index.html
else
	open ./coverage_report/index.html
endif
	rm -rf *.gcda *.gcno *.info

.PHONY : gcov_report

style:
	@cp ../materials/linters/.clang-format .
	clang-format -n $(SRC_FILES)
	clang-format -i $(SRC_FILES)
	@rm -rf .clang-format

.PHONY : style
