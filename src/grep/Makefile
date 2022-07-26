FLAGS=gcc  -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE -g #-fsanitize=address# -fanalyzer

all:s21_grep 
	cp -R *.dSYM test

s21_grep: s21_grep.c 
	$(FLAGS) s21_grep.c -o s21_grep

testus: test/test_combinations.c test/s21_grep_test.c
	gcc test/test_combinations.c test/s21_grep_test.c -o testus -lcheck
	@cp testus ./test
	@cp s21_grep ./test
lint:
	cp ../../materials/linters/CPPLINT.cfg ./ 
	cp ../../materials/linters/CPPLINT.cfg ./test/	
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h ./test/*.c ./test/*.h
	
	rm *.cfg

clean:
	-rm *.out 
	-rm s21_grep
	-rm testus
	-rm ./test/tmp*
	-rm -rf *.dSYM ./test/*.dSYM
	-rm -rf ./test/testus ./test/s21_grep 
