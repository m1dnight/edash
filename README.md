# E-Ink Dashboard 

![Front of the frame](https://raw.githubusercontent.com/m1dnight/edash/master/screen.jpg)
![Rear of the frame](https://raw.githubusercontent.com/m1dnight/edash/master/rear.jpg)

# Hardware

 * E-ink display https://www.waveshare.com/7.5inch-e-paper-c.htm
 * ESP32 with driver board for e-ink included https://www.waveshare.com/wiki/E-Paper_ESP32_Driver_Board
 * Battery shield https://nl.aliexpress.com/item/4001242992784.html?spm=a2g0s.9042311.0.0.6f614c4dNXKuKb
 * Ikea frame https://www.ikea.com/nl/nl/p/ribba-fotolijst-zwart-50378448/
 * Any 18650 battery 

# Compiling for the ESP32 

 * Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` in "Additional Boards Managers URLs" in preferences.
 * Install `esp32` in boards manager.
 * Copy the `esp32-waveshare-epd` folder to your sketchbook location (see preferences).
 * In Arduino IDE select `DOIT ESP32 DEVKIT v1`.
 * Baud rate is 115200.
 * Code away!

# Running the screenshotter 

The screenshotter will take a screenshot of any webpage (preferrably in the right resolution, 640x384) and turns it into a binary blob.
The ESP32 can technically show any jpeg image, but to reduce powerconsumption I chose to do that on the backend.
In essence, this script takes a screenshot and turns it into a binary blob where 8 pixels are grouped into a single byte. 
A file is generated for the black/white screen and for the yellow/white part of the screen. Both are fetched by the ESP32 and shown on the e-ink.

 * Build the `screenshotter/` Docker with `cd screenshotter/ && make` 

I personally have a webapp running on my smart meter that generates a special webpage that's small enough. 
You can find that software here: https://github.com/m1dnight/homedash


