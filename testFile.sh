#!/bin/bash
if [ $# -ne 4 ]
then
  echo Wrong Input
  # exit 1
fi

for((i=0;i<=1000;i++))
do
  t=`expr $RANDOM % 9999`; #id
  let id=t+1;
  echo -n "${id} "

  c=${1-`shuf -n 1 Data/countries.txt`} #country
  echo -n "${c} "

  t=`expr $RANDOM % 120`; #age
  let a=t+1;
  echo -n "${a} "

  v=${1-`shuf -n 1 Data/viruses.txt`} #virus
  echo -n "${v} "

  t=`expr $RANDOM % 100`;
  let tmp=t+1;
  if [ ${tmp} -gt 50 ]
  then
    vacced="YES"
    t=`expr $RANDOM % 30`;
    let d=t+1;
    t=`expr $RANDOM % 12`;
    let m=t+1;
    t=`expr $RANDOM % 601`;
    let y=t+1700;
    vacced="${vacced} ${d}-${m}-${y}";

  else
    vacced="NO"
  fi

  echo -n "${vacced} "

  echo
done
# echo $fullName
