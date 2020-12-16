# /usr/bin/bash

clang++ -pipe -O2 *.cpp -lssl -lcrypto -o build/main
