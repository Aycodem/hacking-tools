#!/usr/bin/env python3 


sequence_str = "112 105 99 111 67 84 70 123 98 52 100 95 98 114 111 103 114 97 109 109 101 114 95 98 56 100 55 50 55 49 102 125"

# Split the sequence string into individual numbers
numbers_str = sequence_str.split()

# Convert each number from string to integer
sequence = [int(num) for num in numbers_str]

for i in sequence:
	flag=chr(i)
	print(flag,end="")
