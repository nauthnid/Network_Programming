#!/bin/bash
# client.sh

nc serverip 1234 | while read -r line; do
    echo "Alice: $line"
done
