#!/bin/bash
# Artillery OS bootable ISO creator script

# STDIO Info colors
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo -e "$GREEN Artillery OS bootable ISO creator script $NC\n\n"

# check the dependency
GENISOIMAGE_PATH=`which genisoimage`
if [ -z $GENISOIMAGE_PATH ]; then
    echo "ERROR: The program genisoimage must be installed"
    exit 1
fi

set -e 

ISO_FOLDER="iso"
MODULE_FOLER="module"
GRUB_CFG_LOCATION="./scripts/grub.cfg"
GRUB_MODULES_LOCATION="./kernel/modules"

mkdir -p $ISO_FOLDER
mkdir -p $ISO_FOLDER/boot
mkdir -p $ISO_FOLDER/boot/grub
mkdir -p $ISO_FOLDER/modules

echo -e "$YELLOW[INFO]$NC copying kernel.elf to iso/boot/..."
cp kernel.elf iso/boot/kernel.elf
echo -e "$GREEN[DONE]$NC copying kernel.elf to iso/boot/...\n"

echo -e "$YELLOW[INFO]$NC copying ./scrtipts/grub.cfg to iso/boot/grub/..."
cp $GRUB_CFG_LOCATION iso/boot/grub/grub.cfg
echo -e "$GREEN[DONE]$NC copying ./scrtipts/grub.cfg to iso/boot/grub/...\n"

echo -e "$YELLOW[INFO]$NC copying test_module to $ISO_FOLDER/modules"
echo "$GRUB_MODULES_LOCATION/test_module"
cp $GRUB_MODULES_LOCATION/test_module $ISO_FOLDER/modules/
echo -e "$GREEN[DONE]$NC copying test_module to $ISO_FOLDER/modules\n"

echo -e "$YELLOW[INFO]$NC copying test_module to $ISO_FOLDER/modules"
echo "$GRUB_MODULES_LOCATION/initrd.img"
cp $GRUB_MODULES_LOCATION/initrd.img $ISO_FOLDER/modules/
echo -e "$GREEN[DONE]$NC copying initrd.img to $ISO_FOLDER/modules\n"

echo -e "$YELLOW[INFO]$NC generating ISO..."
grub-mkrescue --output=artillery.iso iso
echo -e "$GREEN[DONE]$NC ISO Location: ./artillery.iso!\n"

#echo -e "$YELLOW[INFO]$NC Removing ./iso foler..."
#rm -rf $ISO_FOLDER
#echo -e "$GREEN[DONE]$NC Removing ./iso foler...\n"