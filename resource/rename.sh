#!/bin/bash

prefix="normal"  # 替换为你的前缀

# 遍历文件 ***-1 到 ***-10
for i in {1..13}; do
    # 检查文件是否存在
    if [ -f "${prefix}-${i}.png" ]; then
        # 计算新编号（1→0, 2→1, ..., 10→9）
        new_num=$((i - 1))
        # 重命名文件
        mv "${prefix}-${i}.png" "${prefix}-${new_num}.png"
        echo "Renamed: ${prefix}-${i}.png -> ${prefix}-${new_num}.png"
    else
        echo "File ${prefix}-${i}.png not found, skipping."
    fi
done

echo "Renaming complete!"
