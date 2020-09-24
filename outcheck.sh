#!/bin/bash


touch output.txt

./$1 Units/a.txt Units/b.txt > output.txt
./$1 Units/a.txt Units/c.txt >> output.txt
./$1 Units/b.txt Units/a.txt >> output.txt
./$1 Units/b.txt Units/c.txt >> output.txt
./$1 Units/c.txt Units/a.txt >> output.txt
./$1 Units/c.txt Units/b.txt >> output.txt

diff output.txt $2