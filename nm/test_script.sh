#!/bin/bash

for file in ./$1/*; do
	echo "---------------------------------"
	echo "$(basename "$file")"
	./ft_nm $file > /tmp/result_ft_nm;
	nm $file > /tmp/result_nm;
	diff /tmp/result_ft_nm /tmp/result_nm;
	echo "---------------------------------"
done
