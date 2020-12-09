#!/bin/bash 

website=$1

# Create the screenshot in .png format using headless chrome.
# This creates /data/screenshot.jpg
cd /data/
/bin/sh /mkscreenshot $website

# Split the image into the black part and the yellow part.
# This creates /data/black.bmp and /data/color.bmp 
python /app/process.py /data/screenshot.png

# # Turn the black.bmp and color.bmp into binary blobs for the e-ink.
python /app/bmp2bin.py /data/color.bmp /data/yellow.dat 
python /app/bmp2bin.py /data/black.bmp /data/image.dat 

# Cleanup 
# cd /data/ && rm -f screenshot.png black.bmp color.bmp
