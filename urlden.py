#!/usr/bin/env python3 

import urllib.parse 

print("1.Encode url")
print("2.Decode url")

options= input("Choose from 1 or 2 in given option: ")

match options:
	case "1":
		string=str(input("Enter the url here: "))
		print("--" *40 )
		print(urllib.parse.quote(f"""{string}"""))
		print("--" *40 )
	case "2":
		string=str(input("Enter the encoded url here: "))
		print("--" *40 )
		print(urllib.parse.unquote(f"""{string}"""))
		print("--" *40 )
	case _:
		print("invalid input x-x-x")
