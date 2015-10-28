#!/bin/bash

FILES=../audio/*.wav
OUTPUT=sounds.c

echo "Removing $OUTPUT..."
rm $OUTPUT

for f in $FILES
do
    echo "Processing $f file..."
    
    ./soundConverter $f "${f%%.*}"
done
