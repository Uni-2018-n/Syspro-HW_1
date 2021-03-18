#!/bin/bash
if [ $# -ne 4 ]
then
  echo Wrong Input
  exit 1
fi
#$(( (( `date+%N` / 1000) % BASE)+1))
OUTFILE=input.txt;
touch "${OUTFILE}"; rm "${OUTFILE}"; touch "${OUTFILE}";
c=( `shuf -r -n$3 $2` ) #array of countries
v=( `shuf -r -n$3 $1` ) #array of viruses
i=0;
while [ $i -lt "$3" ]
  do
    t=`expr $RANDOM % 9999`; #id
    let id=t+1;
    echo -n "${id} "

    t=`expr $RANDOM % 12`;
    let nam=t+3;
    fn=`shuf -zer -r -n$nam {a..z} | tr -d '\0'`
    echo -n "${fn} "

    t=`expr $RANDOM % 12`;
    let nam=t+3;
    ln=`shuf -zer -r -n$nam {a..z} | tr -d '\0'`
    echo -n "${ln} "

    cc=${c[$i]};
    echo -n "${cc} "

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
    i=$(($i+1))
    if [ $4 -eq 1 ] && [ $i -lt "$3" ]
    then
      t=`expr $RANDOM % 100`;
      let p=t+1;
      while [ $p -lt 20 ] && [ $i -lt "$3" ]
      do
        echo -n "${id} ${fn} ${ln} ${cc} ${a} "
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
        t=`expr $RANDOM % 100`;
        let p=t+1;
        i=$(($i+1))
      done

    fi
  done > "$OUTFILE"
# echo $fullName













exit 0
