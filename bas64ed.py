#!/usr/bin/env python3 

import base64 

print("1.Encode to base64")
print("2.Decode from base64")

input_string= input("Choose what you wanna do: ")

if input_string == "1":
	print("****************************************")
	string =input("Enter the string to encode:  ")
	encode_string=string.encode()
	print("****************************************")
	print("The output is: " + base64.b64encode(encode_string).decode())
elif input_string == "2":
	print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
	encode_bas64 =input("Enter your base64 string to decode: ")
	print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
	print("The output is : " + base64.b64decode(encode_bas64).decode())
else: 
	print("Pls choose between 1 and 2")

