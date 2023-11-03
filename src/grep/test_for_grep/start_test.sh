#!/bin/bash

declare -a option=(" " "-n" "-i" "-c" "-v" "-l" "-h" "-s" "-o")

declare -a files=("s21_greptest1.txt" "s21_greptest2.txt")

declare -a patterns=("-e HELLO" "-e hello" "-f patterns.txt" "-f patterns.txt")

TRUE=0
FALSE=0
ALL=0

for opt1 in "${option[@]}"; do
	for opt2 in "${option[@]}"; do
		for file in "${files[@]}"; do
			if [ "$opt1" != "$opt2" ]
			then
				for ptrn in "${patterns[@]}"; do
					rm -fr diff_1.txt diff_2.txt
					grep $ptrn $opt1 $opt2 $opt3 $opt4 $file >> diff_1.txt
					../s21_grep $ptrn $opt1 $opt2 $opt3 $opt4 $file >> diff_2.txt

					if cmp "-s" diff_1.txt diff_2.txt
					then 
						echo  "$ptrn $opt1 $opt2 $opt3 $opt4 $file $TRUE TRUE"
						((TRUE++))
					else
						echo "$ptrn $opt1 $opt2 $opt3 $opt4 $file $FALSE FALSE"
						echo "$ptrn $opt1 $opt2 $opt3 $opt4 $file $FALSE FALSE" >> false.txt
						((FALSE++))
					fi
					((ALL++))
				done
			fi
		done
	done
done

echo "_____F_OPTION_FAIL_TEST______"

grep -f file lol >> diff_1.txt
../s21_grep -f file lol >> diff_2.txt

if cmp "-s" diff_1.txt diff_2.txt
then 
	echo  "-f file lol $TRUE TRUE"
	((TRUE++))
else
	echo "-f file lol $FALSE FALSE"
	((FALSE++))
fi
((ALL++))

echo "_____FILE_FAIL_TEST_________"

grep -f pattern.txt lol >> diff_1.txt
../s21_grep -f pattern.txt lol >> diff_2.txt

if cmp "-s" diff_1.txt diff_2.txt
then 
	echo  "-f pattern.txt lol $TRUE TRUE"
	((TRUE++))
else
	echo "-f pattern.txt lol $FALSE FALSE"
	((FALSE++))
fi
((ALL++))

echo "TRUE  |   $TRUE"
echo "------|---------"
echo "FALSE |   $FALSE"
echo "------|---------"
echo "ALL   |   $ALL"