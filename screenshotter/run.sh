#!/bin/bash 

website=$1

docker run -i --rm -v $(pwd):/data m1dnight/screenshotter $1

# Send to webspace.
scp yellow.dat christophe@earth.local:/home/christophe/public_html/yellow.dat 
scp image.dat christophe@earth.local:/home/christophe/public_html/image.dat 

# Cleanup 
rm -f yellow.dat image.dat 