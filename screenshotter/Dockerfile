FROM python:alpine

# Stuff for taking a screenshot from a webpage.

# Install chromium and chromedriver
RUN apk update 
RUN apk add --no-cache    \
    dumb-init             \
    chromium              \
    chromium-chromedriver \ 
    python3               \  
    py-pip                \ 
    make automake gcc g++

RUN apk add --no-cache zlib
RUN apk add --no-cache python3-dev jpeg-dev zlib-dev musl-dev

# Replace chromium binary with a script that has some default options
RUN mv /usr/lib/chromium/chrome /usr/lib/chromium/chrome-bin
ADD mkscreenshot /

# Add the image processing scripts.
ADD process.py /app/
ADD requirements.txt /app/

WORKDIR /app 
RUN pip3 install -r requirements.txt 

# Add the binary blob generation scripts.
ADD bmp2bin.py /app/
ADD requirements.txt /app/

WORKDIR /data

ADD screenshot.sh / 
ENTRYPOINT ["/bin/sh", "/screenshot.sh"]