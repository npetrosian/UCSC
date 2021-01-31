#!/bin/bash 
for file in *
do 
	lineCount=1
	while read line
	do
		if [ $(($lineCount % 2)) == 0 ] 
		then
			echo $file: $line
		fi
		((lineCount++))
	done < $file
done
