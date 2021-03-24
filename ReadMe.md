### Koala WiFi Throttle

<img width=300 align=right src=https://i.imgur.com/SMV6n7q.jpg>

Koala is a JMRI compatible WiFi throttle 
that implements more realistic control and behavior of a steam locomotive.
It implements steam locomotive throttle, reverser and brakes.
Speed is based on
tractive effort, train resistance, grade, brake force, train mass and
the application of Newton's Laws.
Koala is targeted to those interested in micro-operation,
realistic operation of a locomotive and train.

The current design uses an
 * [TTGO-Koala ESP32](http://www.lilygo.cn/prod_view.aspx?TypeId=50033&Id=1125)
 * 64x64 OLED display (hopefully 128x128),
 * rotary encoder for automatic (Westinghouse) brake control
 * rotary encoder for independent brake control
 * potentiometer for throttles
 * potentiometer for reversing
 * 16 buttons for various operations: menu, light, sounds
 * USB Type-C serial interface for reprogramming, diagnostics and configuration

Configuration parameters can be edited using the USB serial interface.
Parameters include
 * network SSID and password
 * JMRI IP address and port
 * locomotive DCC address, mph-to-DCC speed factor and engine type
 * engine descriptions specify driver diameter, cylinder dimensions,
   boiler pressure, locomotive and tender weights

OLED display and menu buttons select locomotive to operate and
can be used to edit configuration parameters but may be tedious.
OLED display can be used to update number of cars in train
determining tonnage and will affect performance.

Operation requires proper use of throttle,
reverser affecting direction and cutoff,
air and independent brake settings.

<!-- -----------------------------------------------------  ---------------- -->
<hr>
<p align=right>
<i>Greg Ciurpita - March 2021</i>
