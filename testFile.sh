#!/bin/bash
if [ $# -ne 4 ]
then
  echo Wrong Input
  # exit 1
fi
#id
temp=`expr 9999 - 1 + 1`;
temp=`expr $RANDOM % $temp`;
let id=temp+1;
echo $id
cnum=${1-`wc -l < Data/countries.txt`}
echo "${cnum}"
let mcnum=${cnum}-1+1;

vnum=${1-`wc -l < Data/viruses.txt`}
echo "${vnum}"
let mvnum=${vnum}-1+1;

for((i=0;i<=10;i++))
do
  c=`expr $RANDOM % $mcnum`;
  # get c line from Data/countries.txt
  v=`expr $RANDOM % $mvnum`;
  # get v line from Data/countries.txt
done
# echo $fullName
