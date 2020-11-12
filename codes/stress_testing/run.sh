#!/bin/bash

# Runs a.cpp infinitely againist a gen.cpp input.
# Stops if there's an error like assertion error.

g++ -std=c++17 gen.cpp -o gen
g++ -std=c++17 a.cpp -o a

for((i=1;;i++)); do
	echo $i
	./gen $i > in
  time	./a < in > o1
  if [[ $? -ne 0 ]]; then
    break
  fi
done

cat in
