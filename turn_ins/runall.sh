#!/bin/bash

function compile_all() {
  for f in *.c; do
    gcc -Wall $f -o ${f%.*}
  done
}

compile_all

#echo 1 | exec ./exercise1

# ./dec2bin 255 | ./bin2hec
