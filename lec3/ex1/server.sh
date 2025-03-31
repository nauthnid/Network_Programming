#!/bin/bash
# server.sh

nc -nvlp 1234 | while read -r line; do
    echo "Bob: $line"
done
