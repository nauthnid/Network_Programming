#!/bin/bash

echo -e "HTTP/1.1 200 OK\r\nConnection: close\r\nDate: \$(date)\r\nServer: netcat special deal\r\nContent-Length: 136\r\nContent-Type: text/html; charset=utf-8\r\nCache-Control: max-age=60\r\n\r\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title>Page Title</title>\r\n</head>\r\n<body>\r\nCurrent date is: \$(date)\r\n</body>\r\n</html>"
while true; do
	while true; do
   	      ./webpage.sh | nc -l -p 8080
	done
done
