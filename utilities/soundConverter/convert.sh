#!/bin/bash

FILES=../audio/*.wav
OUTPUT=sounds.c

echo "Removing $OUTPUT..."
rm $OUTPUT

for f in $FILES
do
    # remove path from filename
    pathless_file=${f##*/}

    echo "Processing $pathless_file file..."

    sound_name=${pathless_file%.*}
    
    ./soundConverter $f $sound_name
done
