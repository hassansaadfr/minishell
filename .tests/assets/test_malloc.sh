#!/bin/bash

# Run this script like this :
# ./test_malloc.sh 1 100
# ./test_malloc.sh START END

LIMIT=1
START=$1
END=$2

val()
{
	valgrind --leak-check=full --tool=memcheck --show-reachable=yes --suppressions=file --errors-for-leak-kinds=all --show-leak-kinds=all --error-exitcode=1 ./minishell
}

for value in $(seq $START $END)
do
	LIMIT=$value
	yes | val
	if [ $? -ne 0 ]
	then
		printf ERROR at $value mallocs
	fi
done
