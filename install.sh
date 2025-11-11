#!/bin/bash

set -e

TEDILANG_INSTALL_PATH="/usr/local/bin/tedilang"

tput smcup
trap 'tput rmcup; exit 1' INT

printf "\e[33mte\e[36md\e[34mila\e[35mn\e[31mg\e[0m \e[1mInstaller\e[0m"

printf "\n\e[37m─────────────────\e[0m\n"

if [ -e $TEDILANG_INSTALL_PATH ]; then
    printf "\e[32m✔ \e[37mtedilang is already installed — it will be updated.\e[0m"
else
    printf "\e[31m✖ \e[37mtedilang is not installed.\e[0m"
fi

printf "\n\n\n"

printf "\e[36m→ Press Enter to install..\n\e[0m"
printf "\e[31m→ Press [R] to uninstall..\n\e[0m"
read

cp ./bin/tedilang $TEDILANG_INSTALL_PATH

echo "tedilang successfully installed! Press Enter to continue..."
read

tput rmcup