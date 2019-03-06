#!/bin/bash

echo "Masukkan kata : "
read string

i=0
len=${#string}
mid=$(($len/2))

while [ $i -lt $mid ]
  do
    if [ "${string:$i:1}" != "${string: -$(($i+1)):1}" ]
      then
      echo "$string != palindrom"
      exit
    fi
    i=$(($i+1))
done
echo "$string = palindrom"
