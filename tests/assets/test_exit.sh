#!/bin/bash

# Run this script like this :
# ./test_exit.sh 1 100
# ./test_exit.sh START END

LIMIT=1
START=$1
END=$2

MSH_RET=0
BASH_RET=0

msh()
{
	echo "exit $1" | ./minishell
}

bsh()
{
	echo "exit $1" | bash --posix
}

for value in $(seq $START $END)
do
	LIMIT=$value
	msh $value
	MSH_RET=$?
	bsh $value
	BASH_RET=$?
	if [ $MSH_RET != $BASH_RET ]
	then
		printf "returned $MSH_RET instead of $BASH_RET\n"
	fi
done
