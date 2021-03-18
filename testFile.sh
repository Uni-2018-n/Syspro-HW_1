#!/bin/bash
if [ $# -ne 4 ]
then
  echo Wrong Input
  # exit 1
fi
#$(( (( `date+%N` / 1000) % BASE)+1))
OUTFILE=input.txt;
db=1;
touch "${OUTFILE}"; rm "${OUTFILE}"; touch "${OUTFILE}";
test=10000;
c=( `shuf -n $test Data/countries.txt` ) #array of countries
v=( `shuf -n $test Data/viruses.txt` ) #array of viruses
i=0;
while [ $i -lt "$test" ]
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

    cc=${c[`expr $i % 111`]};
    echo -n "${cc} "

    t=`expr $RANDOM % 120`; #age
    let a=t+1;
    echo -n "${a} "

    echo -n "${v[`expr $i % 141`]} "

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
    if [ ${db} -eq 1 ] && [ $i -lt "$test" ]
    then
      t=`expr $RANDOM % 100`;
      let p=t+1;
      while [ $p -lt 20 ] && [ $i -lt "$test" ]
      do
        echo -n "${id} ${fn} ${ln} ${cc} ${a} "
        t=`expr $RANDOM % 111` #TODO use len of file
        let dup=t+1;
        echo -n "${v[$dup]} "

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
