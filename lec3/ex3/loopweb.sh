#!/bin/bash

while true; do
  echo -e "HTTP/1.1 200 OK\nConnection: close\nDate: $(date)\nServer: netcat special deal\nContent-Length: 136\nContent-Type: text/html; charset=utf-8\nCache-Control: max-age=60\n"
  echo -e "<!DOCTYPE html>\n<html>\n<head>\n<title>Page Title</title>\n</head>\n<body>\nCurrent date is: $(date)\n</body>\n</html>\n"

  sleep 1  
done | nc -l -p 8080
