FLAGS=gcc -Wall -Werror -Wextra -std=c11 -DGNU_SOURCE -g 

all: s21_cat

s21_cat: s21_cat.c
	$(FLAGS) s21_cat.c -o s21_cat

lint:
	cp ../../materials/linters/CPPLINT.cfg ./ 
	python3 ../../materials/linters/cpplint.py --extensions=c *.c 
	rm *.cfg
clean:
	rm -rf s21_cat *.dSYM
