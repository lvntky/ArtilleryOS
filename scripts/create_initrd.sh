#!/bin/bash

YELLOW='\033[1;33m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo -e "$GREEN Artillery OS initrd creator script $NC\n\n"
echo -e "$YELLOW[INFO]$NC Creating example file $NC\n"

cd ./kernel/fs/tempfs


echo -e "$YELLOW[INFO]$NC Compiling filesystem_generator.c $NC\n"
gcc filesystem_generator.c -o filesystem_generator
echo -e "$GREEN[DONE]$NC Compiling filesystem_generator.c $NC\n"

echo -e "$YELLOW[INFO]$NC Creating initrd.img $NC"
./filesystem_generator test.txt test.txt
echo -e "$GREEN[DONE]$NC Creating initrd.img $NC\n"

echo -e "$YELLOW[INFO]$NC Copying initrd.img to GRUB Module path $NC"
cp initrd.img ../../modules/
echo -e "$GREEN[DONE]$NC Copying initrd.img to GRUB Module path $NC\n"

echo -e "$GREEN[DONE]$NC Ready for ISO with! $NC\n"