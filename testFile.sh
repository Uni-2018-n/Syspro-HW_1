#!/bin/bash
if [ $# -ne 4 ]
then
  echo Wrong Input
  exit 1
fi
#id
id=$(( $RANDOM % (9999 - 1 + 1 ) + 1 ))

# fullName
len=$(( $RANDOM % (12 - 3 + 1 ) + 3 ))
echo $len
fullName=""
for (( i=0; i<$len ; i++ ))
do
  char=$(( $RANDOM % (122 - 97 + 1 ) + 97 ))
  tchar= printf \\$(printf '%03o' $char)
  fullName="$fullName$tchar"
done
# echo $fullName
