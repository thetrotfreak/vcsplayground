#!/bin/sh
# shell script for https://github.com/spotify/echoprint-codegen

# suppress Ubuntu on-launch system information
touch .hushlogin

# install dependencies
sudo apt-get update && sudo apt-get upgrade -y
sudo apt-get install build-essential cmake libboost-all-dev libtag1-dev zlib1g-dev ffmpeg -y

git clone https://github.com/spotify/echoprint-codegen.git spotify-echoprint-codegen && cd spotify-echoprint-codegen/src
sudo make install
