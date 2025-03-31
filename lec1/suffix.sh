#!/bin/bash
# check the number of argument, in this case it equal to 2
if [ $# -ne 2 ]
then
  echo "Please enter the file name and the suffix."
  exit 1
fi

# check the file is exist or not
if [ ! -e $1 ]
then
  echo "File '$1' not exist!"
  exit 1
fi

# rename the file name
mv $1 $1$2
