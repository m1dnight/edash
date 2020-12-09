from PIL import Image
import numpy as np
from bitstring import BitArray
import sys

img = Image.open(sys.argv[1])
img_black = np.array(img)
img_color = img_black.copy()
img_orig = img_black.copy()

(height, width, bytes) = img_black.shape
for y in range(height):
    for x in range(width):
        # Fill array with white.
        img_color[y,x] = 255,255,255,255
        img_black[y,x] =255,255,255,255

        test = img_orig[y,x]
        r,g,b,a = img_orig[y,x]
        luminance = 0.2126*r + 0.7152*g + 0.0722*b
        # If the pixel is black or grey we write it in the black matrix.
        if r == g == b and r < 240:
            img_black[y,x] = 0,0,0,0
        # The pixel is white.
        elif r == g == b: 
            img_black[y,x] = 255,255,255,255
            img_color[y,x] = 255,255,255,255 
        # The pixel is colored.
        else:
            img_color[y,x] = 0,0,0,0


data = Image.fromarray(img_color)
data.save("color.bmp")
data = Image.fromarray(img_black)
data.save("black.bmp")