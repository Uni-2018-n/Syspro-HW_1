#!/bin/bash
if [ $# -ne 4 ]
then
  echo Wrong Input
  # exit 1
fi
#$(( (( `date+%N` / 1000) % BASE)+1))
OUTFILE=input.txt;
db=0;
touch "${OUTFILE}"; rm "${OUTFILE}"; touch "${OUTFILE}";
test=10;
c=( `shuf -n $test Data/countries.txt` ) #array of countries
v=( `shuf -n $test Data/viruses.txt` ) #array of viruses
for((i=0;i<$test;i++))
do
  t=`expr $RANDOM % 9999`; #id
  let id=t+1;
  echo -n "${id} "

  t=`expr $RANDOM % 12`;
  let nam=t+3;
  fn=`shuf -zer -n$nam {a..z} | tr -d '\0'`
  echo -n "${fn} "

  t=`expr $RANDOM % 12`;
  let nam=t+3;
  ln=`shuf -zer -n$nam {a..z} | tr -d '\0'`
  echo -n "${ln} "


  echo -n "${c[$i]} "

  t=`expr $RANDOM % 120`; #age
  let a=t+1;
  echo -n "${a} "

  echo -n "${v[$i]} "

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
done > "$OUTFILE"
# echo $fullName

exit 0
