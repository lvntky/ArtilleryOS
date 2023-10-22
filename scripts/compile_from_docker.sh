#!/bin/bash
GREEN='\e[32m'
RESET='\e[0m'
PREFIX='[Artillery OS]]'

echo -e "${GREEN}${PREFIX}${RESET} Compiling the source code...\n"

mkdir -p build
make clean
make all

echo -e "${GREEN}${PREFIX}${RESET} ISO file has been created!\n"
