Arduino code

* __Guggenhat_Neopixel_Test__: light a few LEDs at a time to limit current draw so it's within the limit of the Arduino +5V pin (less than 450 ma)
    * __DO NOT__ use the NeoPixel library's “strandtest” example unless you have a separate high current supply! It lights all the LEDs at once — more power than the Arduino's USB input can handle. 
  * Changes: edit data pin number and number of LEDs
  * Source: https://learn.adafruit.com/guggenhat-bluetooth-le-wearable-neopixel-marquee-scrolling-led-hat-display/overview
