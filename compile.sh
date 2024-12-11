#!/bin/bash

clear
gcc src/main.c src/server.c src/handler.c -o main -Iinclude
./main
