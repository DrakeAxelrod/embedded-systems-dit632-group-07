#!/bin/bash

function compile_all() {
  for f in *.c; do
    echo "compiling $f"
    gcc $f -o ${f%.*}
  done
}


compile_all

echo "running dec2bin without pipe"
./dec2bin 255
./dec2bin 256
./dec2bin 65535
./dec2bin 65535

echo "piping output of dec2bin to bin2hec"
./dec2bin 255 | ./bin2hec
./dec2bin 256 | ./bin2hec
./dec2bin 65535 | ./bin2hec
./dec2bin 65535  | ./bin2hec

echo "running bin2hec without pipe"
./bin2hec 11111111
./bin2hec 0000000100000000
./bin2hec 1111111111111111
./bin2hec 1111111111111111
