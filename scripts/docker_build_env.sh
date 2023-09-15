current_date=$(date)
echo "\033[32m[ARTILLERY OS] -- $current_date --\033[0m    Entering the build enviroment..."

docker build -t artilleryos-build-env ./buildenv
docker run --rm -it -v "$(pwd)":/root/env artilleryos-build-env

echo "\033[32m[ARTILLERY OS] -- $current_date --\033[0m    Exiting the build enviroment..."