#!/bin/bash
# check if it is single integer argument
if [ $# -ne 1 ]
then
  echo "Please enter one single integer!"
  exit 1
fi

# check the argument is an integer or not
if ! [[ $1 =~ ^-?[0-9]+$ ]]     #regex to check integer
then
  echo "Argument must be an integer!"
  exit 1
fi

# doubles its value
result=$((2*$1))

# print the result to console
echo $result
