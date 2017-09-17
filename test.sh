set -e
for number in 1 2 3 4 5 6 7 8c 8m 9c 9m 10 11 12 13
do
    echo "test $number"
    g++ -std=c++14 -Wall -Werror -O2 -o test$number test$number.cpp
    ./test$number > result$number.txt
done