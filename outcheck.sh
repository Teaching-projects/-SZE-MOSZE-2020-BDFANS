#!/bin/bash


touch output.txt

./$1 $3 > output.txt

diff output.txt $2