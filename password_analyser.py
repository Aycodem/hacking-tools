#!/usr/bin/env python3

import re

def password_analyzer(password):
	
	length_ok = len(password) >= 8

	#check for uppercase 

	uppercase_check = any(char.isupper() for char in password)

	#check for lowercase

	lowercase_check = any(char.islower() for char in  password)

	#check for digits

	digit_check = any(char.isdigit() for char in password)

	#check for special_character

	special_char = re.search(r'[!@#$%^&*;:()-+{}?><.,|\/]',password) is not None

	if length_ok and uppercase_check and lowercase_check and digit_check and special_char:
		return "Strong password"
	elif length_ok and (uppercase_check or lowercase_check) and digit_check:
		return "Moderate"
	else:
		return "Weak"


input_pass =input("Enter your password:\t")

print(password_analyzer(input_pass))








