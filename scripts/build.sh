current_date=$(date)
echo "[ARTILLERY OS] -- $current_date --    Building the kernel..."

make build-x86_64
exit