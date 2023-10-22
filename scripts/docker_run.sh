#!/bin/bash
GREEN='\e[32m'
RESET='\e[0m'

echo -e "${GREEN}[Artillery OS]${RESET} Entering the build enviroment\n"

# Run the Docker container
sudo docker run -it artillery-build-env:latest

