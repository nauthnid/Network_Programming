#!/bin/bash

# Kiểm tra xem chương trình có nhận đúng số lượng tham số không
if [ $# -ne 2 ]; then
    echo "Usage: $0 <filename> <suffix>"
    exit 1
fi

# Lấy tên tệp tin và hậu tố từ các tham số đầu vào
filename=$1
suffix=$2

# Kiểm tra xem tệp tin có tồn tại không
if [ ! -f "$filename" ]; then
    echo "File not found: $filename"
    exit 1
fi

# Tạo tên mới bằng cách thêm hậu tố vào cuối tên tệp tin
new_filename="${filename}${suffix}"

# Đổi tên tệp tin
mv "$filename" "$new_filename"

# In ra thông báo thành công
echo "File renamed to: $new_filename"
