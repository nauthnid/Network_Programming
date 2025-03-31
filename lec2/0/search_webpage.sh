#!/bin/bash

# function to search a webpage for a search string
search_webpage() {
    local url="$1"
    local search_string="$2"

# show the HTML content of webpage
    local webpage_content
    webpage_content=$(curl -s "$url")

# search string in webpage content
    if echo "$webpage_content" | grep -q "$search_string"; then
        echo "Found $search_string on the webpage $url"
    else
        echo "$search_string not found on the webpage $url"
    fi
}

search_webpage "$1" "$2"
