#!/bin/bash
GREEN='\e[32m'
RESET='\e[0m'

echo -e "${GREEN}[Artillery OS]${RESET} Building docker enviroment for cross-compiler.\n"

sudo docker build -t artillery-build-env .

echo -e "${GREEN}[Artillery OS]${RESET} The build enviroment has been created...\n"
sudo docker images
