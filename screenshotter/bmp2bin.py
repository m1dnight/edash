from PIL import Image
import numpy as np
from bitstring import BitArray
import sys

# Read in the .bmp image and turn it into an array of True/False.
image = Image.open(sys.argv[1])
image= image.convert('1')
pixel_array = np.array(image)
pixel_array = pixel_array.flatten()

# Group into lists of 8 each.
pixels = [pixel_array[k:k+8].tolist() for k in range(0, len(pixel_array), 8)]


# Turn the pixel lists into binary data.
binary = BitArray()
for p in pixels:
    str = ''
    for b in p:
        if b:
            str = str + '1'
        else:
            str = str + '0'
    byte = BitArray(bin=str)
    binary.append(byte)

# Write to binary file.
f = open(sys.argv[2], 'wb')
binary.tofile(f)
f.close()