current_date=$(date)
echo "[ARTILLERY OS] -- $current_date --    Building the kernel..."

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
make clean
make all
exit