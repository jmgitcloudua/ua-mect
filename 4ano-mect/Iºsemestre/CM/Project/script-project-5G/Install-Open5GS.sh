#!/bin/bash

echo -e '\e[34mInstalling MongoDB'
sudo apt update
sudo apt install -y gnupg
wget -qO - https://www.mongodb.org/static/pgp/server-6.0.asc | sudo apt-key add -
echo "deb http://repo.mongodb.org/apt/debian bullseye/mongodb-org/6.0 main" | sudo tee /etc/apt/sources.list.d/mongodb-org-6.0.list
sudo apt update
sudo apt install -y mongodb-org
sudo systemctl start mongod
sudo systemctl enable mongod
echo -e '\e[32mDone'

echo 'Installing Open5GS'
sudo apt update
wget -qO - https://download.opensuse.org/repositories/home:/acetcom:/open5gs:/latest/Debian_11/Release.key | sudo apt-key add -
sudo sh -c "echo 'deb http://download.opensuse.org/repositories/home:/acetcom:/open5gs:/latest/Debian_11/ ./' > /etc/apt/sources.list.d/open5gs.list"
sudo apt update
sudo apt install -y open5gs
echo -e '\e[32mDone'

echo -e '\e[34mInstalling WebUI'
sudo apt update
sudo apt install -y curl
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt install -y nodejs
curl -fsSL https://open5gs.org/open5gs/assets/webui/install | sudo -E bash -
echo -e '\e[32mDone'
