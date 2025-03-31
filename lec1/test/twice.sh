#!/bin/bash

# Kiểm tra xem chương trình có nhận đúng số lượng tham số không
if [ $# -ne 1 ]; then
    echo "Usage: $0 <integer>"
    exit 1
fi

# Lấy giá trị số nguyên từ tham số đầu vào
number=$1

# Nhân đôi giá trị số nguyên
result=$((number * 2))

# In ra kết quả
echo "Result: $result"
