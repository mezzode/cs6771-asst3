for number in 1 2 3 4 ; do \
    g++ -std=c++14 -Wall -Werror -O2 -o test$$number test$$number.cpp; \
    ./test$$number > result$$number.txt; \
done
