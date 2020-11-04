#!/bin/bash


touch output.txt

./$1 $2 > output.txt

diff output.txt $3