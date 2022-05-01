#!/bin/bash 

website=$1

docker run -i --rm -v $(pwd):/data m1dnight/screenshotter $1

# Send to webspace.
mv yellow.dat ${2}/yellow.dat
mv image.dat ${2}/image.dat