#!/bin/bash

declare -a option=("-b" "-e" "-n" "-s" "-t" "-v")

declare -a files=("s21_cattest1.txt" "s21_cattest2.txt" "s21_cattest3.txt")

TRUE=0
FALSE=0
ALL=0

for opt1 in "${option[@]}"; do
	for opt2 in "${option[@]}"; do
		for opt3 in "${option[@]}"; do
			for file in "${files[@]}"; do
				if [ "$opt1" != "$opt2" ] && [ "$opt1" != "$opt3" ] \
            	&& [ "$opt2" != "$opt3" ]
            	then
					rm -fr diff_1.txt diff_2.txt
					cat $opt1 $opt2 $opt3 $opt4 $file >> diff_1.txt
					../s21_cat $opt1 $opt2 $opt3 $opt4 $file >> diff_2.txt

					if cmp "-s" diff_1.txt diff_2.txt
					then 
						echo  "$opt1 $opt2 $opt3 $opt4 $file $TRUE TRUE"
						((TRUE++))
					else
						echo "$opt1 $opt2 $opt3 $opt4 $file $FALSE FALSE"
						((FALSE++))
					fi
					((ALL++))
				fi
			done
		done
	done
done

echo "_____ERROR__TEST______"

cat -qwe lol >> diff_1.txt
./s21_cat -qwe lol >> diff_2.txt

if cmp "-s" diff_1.txt diff_2.txt
then 
	echo  "-qwe lol $TRUE TRUE"
	((TRUE++))
else
	echo "-qwe lol $FALSE FALSE"
	((FALSE++))
fi
((ALL++))

echo "TRUE  |   $TRUE"
echo "------|---------"
echo "FALSE |   $FALSE"
echo "------|---------"
echo "ALL   |   $ALL"