#!/bin/bash

for file in ./$1/*; do
	echo "---------------------------------"
	echo "$(basename "$file")"
	./ft_otool $file > /tmp/result_ft_nm;
	otool -t $file > /tmp/result_nm;
	diff /tmp/result_ft_nm /tmp/result_nm;
	echo "---------------------------------"
done
