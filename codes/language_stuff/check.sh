#!/bin/bash
g++ -std=c++17 gen.cpp -o gen
g++ -std=c++17 a.cpp -o a
g++ -std=c++17 brute.cpp -o brute

for((i=1;;i++)); do
	echo $i
	./gen $i > in
	diff <(./a < in) <(./brute < in) || break
done

cat in
#sed -i 's/\r$//' filename  ----- remover \r do txt