#!/bin/bash

function compile_all() {
  for f in *.c; do
    echo "compiling $f"
    gcc $f -o ${f%.*}
  done
}

function run() {
  compile_all
}

run
run > ./run_script_output.txt
