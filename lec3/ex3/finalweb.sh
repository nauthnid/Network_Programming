#!/bin/bash

# Hàm để tạo nội dung HTML
generate_html() {
    echo -e "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title>Page Title</title>\r\n</head>\r\n<body>\r\nCurrent date is: $(date)\r\n</body>\r\n</html>"
}

# Tạo máy chủ web và cập nhật thông tin ngày giờ khi có kết nối mới
while true; do
    { generate_html; sleep 1; } | nc -l -p 8080 >/dev/null
done
