#!/bin/bash

echo -en "\033[38;5;208m"
echo "================================================================================"
echo "============================== FT_CONTAINERS TEST =============================="
echo "================================================================================"
echo -e "\033[0m"

g++ -Wall -Wextra -Werror -std=c++98 -pedantic -g3 -fsanitize=address main.cpp -o tstd
if [[ $? -ne 0 ]]; then
	echo -e "\033[31mCOMPILATION ERROR\033[0m"
	exit
fi

g++ -Wall -Wextra -Werror -std=c++98 -pedantic -g3 -fsanitize=address -D TFT main.cpp -o tft
if [[ $? -ne 0 ]]; then
	echo -e "\033[31mCOMPILATION ERROR\033[0m"
	exit
fi

./tstd > tstd.results
./tft > tft.results

diff tstd.results tft.results > results.diff

if [[ $? -ne 0 ]]; then
	echo -e "\033[31mERROR\nsee results.diff\033[0m"
	exit
else
	echo -e "\033[32mEverything is working as intended\033[0m"
	rm -rf tstd* tft* results.diff
fi
