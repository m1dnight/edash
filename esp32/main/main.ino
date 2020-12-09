#include <dummy.h>

#include <DEV_Config.h>
#include <EPD.h>
#include <fonts.h>
#include <GUI_Paint.h>

/* Includes ------------------------------------------------------------------*/
#include <WiFi.h>

#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"

#include <HTTPClient.h>

/* SSID and password of your WiFi net ----------------------------------------*/
const char *ssid = "🐼";
const char *password = "";

const char *root_ca =
  "-----BEGIN CERTIFICATE-----\n"
  "-----END CERTIFICATE-----\n";

/*
   Connects the ESP32 to the WiFi network specified at lines 10-11.
   Code from https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/WiFiClient/WiFiClient.ino
*/
void connectWiFi()
{
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Loop and wait for the connection to succeed.
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  // Print succes.
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
}

/*
   Downloads a bmp image from a predefined endpoint.
*/
unsigned char *fetchImage(char *url, int *length)
{
  HTTPClient http;
  unsigned char *arr;
  http.begin(url, root_ca);
  int httpCode = http.GET();
  if (httpCode == 200)
  {
    // Total bytes that are going to be sent over the wire.
    int len = http.getSize();
    int total = len;
    *length = len;

    Serial.printf("Image is %d bytes, should be around 30720\n", len);

    // Allocate all the memory necessary to fit the image.
    arr = (unsigned char *)malloc(sizeof(unsigned char) * total);
    int offset = 0;

    unsigned char buff[128] = {0};

    WiFiClient *stream = http.getStreamPtr();
    while (http.connected() && (len > 0 || len == -1))
    {
      size_t size = stream->available();
      if (size)
      {
        int fetched = (size > sizeof(buff)) ? sizeof(buff) : size;
        int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));

        for (int i = 0; i < fetched; i++)
        {
          int j = offset + i;
          arr[j] = buff[i];
        }
        offset = offset + fetched;

        if (len > 0)
        {
          len -= c;
        } // if
      }   // if
    }     // while
  }       // if
  http.end();
  Serial.println("Fetched image");
  return arr;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup");
  Serial.println("Connecting to WiFi");
  connectWiFi();

  Serial.println("Getting black image");
  int length;
  unsigned char *black = fetchImage("https://example.com/image.dat", &length);
  Serial.println("Getting yellow image");
  unsigned char *yellow = fetchImage("https://example.com/yellow.dat", &length);

  Serial.println("Dev init");
  DEV_Module_Init();

  Serial.println("e-Paper init...");
  EPD_7IN5BC_Init();
  
  Serial.println("e-Paper clear...");
  EPD_7IN5BC_Clear();

  Serial.println("Draw new image");
  EPD_7IN5BC_Display(black, yellow);
  DEV_Delay_ms(2000);

  Serial.println("Put display to sleep");
  EPD_7IN5BC_Sleep();

  Serial.println("Free data from memory");
  free(black);
  free(yellow);
  black = NULL;
  yellow = NULL;

  Serial.println("Update done, going to sleep");

}
void loop()
{
  uint64_t minutes = 60;
  uint64_t microseconds = minutes * 60000000ULL;
  Serial.printf("Sleeping for %u microseconds\n", microseconds);
  esp_sleep_enable_timer_wakeup(microseconds);
  esp_deep_sleep_start();
}
