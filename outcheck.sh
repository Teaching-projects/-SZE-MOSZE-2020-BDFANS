#!/bin/bash


touch output.txt

./$1 Units/a.txt units/b.txt > output.txt
echo "" >> output.txt
./$1 Units/a.txt units/c.txt >> output.txt
echo "" >> output.txt
./$1 Units/b.txt units/a.txt >> output.txt
echo "" >> output.txt
./$1 Units/b.txt units/c.txt >> output.txt
echo "" >> output.txt
./$1 Units/c.txt units/a.txt >> output.txt
echo "" >> output.txt
./$1 Units/c.txt units/b.txt >> output.txt
echo "" >> output.txt

diff output.txt $2