echo -e '\e[34mInstalling MongoDB'
sudo apt update
sudo apt install -y gnupg
wget -qO - https://www.mongodb.org/static/pgp/server-6.0.asc | sudo apt-key add -
echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu focal/mongodb-org/6.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-6.0.list
sudo apt update
sudo apt install -y mongodb-org
sudo systemctl start mongod
sudo systemctl enable mongod
echo -e '\e[32mDone'

echo -e '\e[32mInstalling Open5GS'
sudo add-apt-repository ppa:open5gs/latest
sudo apt update
sudo apt install open5gs
echo -e '\e[32mDone'

echo -e '\e[34mInstalling WebUI'
sudo apt update
sudo apt install -y curl
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt install -y nodejs
curl -fsSL https://open5gs.org/open5gs/assets/webui/install | sudo -E bash -
echo -e '\e[32mDone'
