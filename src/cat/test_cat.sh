read -p "Enter flag" flag
expectedOut="dif1.txt"
actualOut="dif2.txt"

rm -fr $expectedOut $actualOut
cat $flag  test.txt >> $actualOut
./s21_cat $flag test.txt >> $expectedOut

if cmp -s $expectedOut $actualOut;
    then
    echo "True"
    else
    echo "False"
    fi