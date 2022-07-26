#!/bin/bash
FUNC='s21_cat'
FILE=("nonprint_col.txt" "allascii.txt")
# echo ${FILE[*]}
# for i in -b -e -b -s -t -v; do
# for k in ${FILE[*]}; do
# 	echo $k $i
# done
# done

compare (){
	cat $1 $2 > 1.txt
	./${FUNC} $1 $2 > 2.txt
	res=$(diff 1.txt 2.txt)
	echo after result  $1
	if [ -z "${res}" ]; then
		echo  " "$1 $2 "working as intended tm"
		rm 1.txt 2.txt
	else
		echo $1 "test failed"
		echo ${res}
		break
	fi
}

for i in -b -e -n -s -t -v ; do
	for j in ${FILE[*]}; do
		compare $i $j
	done
done

# cat -b allascii.txt > 1.txt
# ./s21_cat -b allascii.txt >2.txt
# res=$(diff 1.txt 2.txt)
# rm 1.txt 2.txt

# if [ -z "${res}" ]; then
# 	echo "working as intended lol"
# else
# 	echo "lmao got'em "
# 	echo ${res}
# fi

