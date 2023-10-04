#!/bin/bash

read -n 1 -s -r -p "Press any key to continue compilation"

gcc -I/usr/include/gtk-3.0 -o main main.c `pkg-config --cflags --libs gtk+-3.0`
clear
echo " => done press ./main to run"