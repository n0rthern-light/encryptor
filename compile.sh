#!/bin/sh

g++ -std=c++20 encryptor/main.cpp encryptor/cryptor.cpp -o ./encryptor/bin/cryptor
chmod +x ./encryptor/bin/cryptor
