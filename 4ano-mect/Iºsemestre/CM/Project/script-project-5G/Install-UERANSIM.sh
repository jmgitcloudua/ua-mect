#!/bin/bash

echo -e '\e[34mInstalling UERANSIM'
sudo apt update
sudo apt install -y cmake make gcc g++ libsctp-dev lksctp-tools iproute2 git
git clone https://github.com/aligungr/UERANSIM
cd ./UERANSIM
make
echo -e '\e[32mDone'
