#!/bin/bash


touch output.txt

./$1 units/a.txt units/b.txt > output.txt
echo "" >> output.txt
./$1 units/a.txt units/c.txt >> output.txt
echo "" >> output.txt
./$1 units/b.txt units/a.txt >> output.txt
echo "" >> output.txt
./$1 units/b.txt units/c.txt >> output.txt
echo "" >> output.txt
./$1 units/c.txt units/a.txt >> output.txt
echo "" >> output.txt
./$1 units/c.txt units/b.txt >> output.txt
echo "" >> output.txt

diff output.txt $2