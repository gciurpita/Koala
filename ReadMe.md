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
<h4> Configuration </h4>

Until the throttle is configured,
it won't be able to connect to WiFi, JMRI or
have a valid DCC loco address.
The OLED will display

<table border=0 align=center> <tr> <td>
WiFi connecting
<br>WiFi-ssid
<br>WiFi-password
</table>

The throttle can be configured through the Arduino IDE serial monitor 
by connecting a USB-c cable between a laptop and throttle and
configuring the IDE for an "ESP32 Dev Module" board and
the USB com port the cable is connected to.

<p>
Pressing the reset button on the ESP32
should produce output similar to below.
If the ESP32 has not been programmed before,
it should fail to open <i>/spiffs/koala.cfg</i>  and
will automatically create (save) it with default values.

<blockquote>
<pre>
...
Koala Throttle - 210324a
cfgLoad: /spiffs/koala.cfg
cfgLoad - fopen: No such file or directory
cfgSave: /spiffs/koala.cfg
</pre></blockquote>

At the top of the serial monitor window is an input box
with a "Send" button to the right.
Single letter commands can be sent to the throttle.
A "?" requests a help screen.

"?" entered
<blockquote> <pre>
cmdMode:
   \# B - set button #
   \# b - set air-brake position
   \# c - set cars to #
     D - set debug to #
     d - display config variables
     E - display configuration variables
     e - switch to cfgMode
     F - list SPIFFS files
     f - toggle decoder function #
   \# i - set independent brake to #
     L - load configuration
   \# l - set loco address to #
     p - switch to pin mode
     R - reset
   \# r - set reverser #
     S - save configuration
   \# t - set throttle #
     v - display state variables
     V - print version
     X - delete SPIFF file
loop: state 0x20 - ST_CFG
engineInit: loco NA_2-6-2, wt 24, maxTe 12000
engineRst:  cylVol 1.38, PSI 180, ftPrev 9.42, revPft 0.106, cycPft 0.424  NA_2-6-2
chkLoco: locoLst -1 to locoIdx 0,
wifiSend: MT-*<;>r
wifiSend: TS0
wifiSend: TS100
loop: state 0x00 -
</pre></blockquote>

The "d" command displays all configuration variables.

"d" entered
<blockquote> <pre>
      name: Koala Throttle
      ssid: WiFi-ssid
  password: WiFi-password
  hostname: 192.168.1.100
      port:  12080
   locoIdx:      0
    loco_1:    100   1.10   4  NA_2-6-2
    loco_2:    200   2.10   1  G-1sas
    loco_3:    300   3.10   2  K-1
    loco_4:    400   4.10   3  T-1
    loco_5:    500   3.20   4  NA_2-6-2
    loco_6:    600   2.20   5  BigBoy
    loco_7:    700   1.20   6  catskill
    loco_8:    800   2.30   7  MILW_4-4-2
    loco_9:    900   3.30   8  MILW_F-6
   loco_10:      0   0.00   0  I-10sa
     eng_0:  61.5  27.0  32.0  2 220 132 146  90  95.0  13.5  88.0   0.0   8.0 2-8-0      I-10sa
     eng_1:  80.0  25.0  28.0  2 200  90 140  90  95.0  19.0  80.0   0.0   8.0 4-6-2      G-1sas
     eng_2:  61.5  30.5  32.0  2 220 160 200 115 108.0  22.2 100.0   0.0   8.0 2-10-2     K-1
     eng_3:  70.0  27.0  32.0  2 240 126 200  90  95.0  13.5  88.0   0.0   8.0 4-8-4      T-1
     eng_4:  36.0  13.0  18.0  2 180  24  34   0   9.0  11.0  40.0   0.0   8.0 2-6-2T     NA_2-6-2
     eng_5:  68.0  23.8  32.0  4 300 270 380 170 150.0  18.0  95.0   0.0   8.0 4-8-8-4    BigBoy
     eng_6:  69.0  22.0  28.0  2 200   0   0   0   0.0   0.0   0.0   0.0   8.0 _          catskill
     eng_7:  84.0  19.0  28.0  2 300  74 140 123  69.0  19.0  80.0   0.0   8.0 4-4-2      MILW_4-4-2
     eng_8:  80.0  26.0  28.0  2 225  86 187 138  80.0  19.0  80.0   0.0   8.0 F-6        MILW_F-6
     eng_9:  84.0  23.5  30.0  2 300 108 207 187  96.5  19.0  82.5   0.0   8.0 F-7        MILW_F-7
    eng_10:  70.0  27.0  32.0  2 320 160 247 189 107.7   0.0   0.0   0.0   8.0 4-8-4      N&W
    eng_11:
loop: state 0x20 - ST_CFG
loop: state 0x00 -
</pre></blockquote>

Configuration variables includes a throttle name,
WiFi network credentials, JMRI IP address and port number.
It includes ten locomotive entries specifying DCC address,
mph-to-DCC speed factor and engine type and
multiple engine parameter descriptions.

The "E" command lists each configuration record, one at a time,
allowing it to be modified by entering new information.
Just pressing the enter key accepts the new information and/or
skips to the next record.

"E" entered
<blockquote> <pre>
cfgEdit:
      name: Koala Throttle
</pre></blockquote>

"my Throttle" entered
<blockquote> <pre>
      name: my Throttle
</pre></blockquote>

"" entered
<blockquote> <pre>
      ssid: WiFi-ssid
</pre></blockquote>

"FiOS-DGHZ0" entered
<blockquote> <pre>
      ssid: FiOS-DGHZ0
</pre></blockquote>

"" entered
<blockquote> <pre>
  password: WiFi-password
</pre></blockquote>

"my-password entered
<blockquote> <pre>
  password: my-password
</pre></blockquote>

Of course you should use the SSID and password
for the same WiFi device that JMRI connects to or
can be accessed through.

"" entered
<blockquote> <pre>
  hostname: 192.168.1.100
</pre></blockquote>

"192.168.1.227" entered
<blockquote> <pre>
  hostname: 192.168.1.227
</pre></blockquote>

"" entered
<blockquote> <pre>
      port:  12080
</pre></blockquote>

"" entered
<blockquote> <pre>
   locoIdx:      0
</pre></blockquote>

"locoIdx" is the default loco record to be used.
It will be updated automatically when different entries are selected
using the OLED interface, but could be changes at this time.

"" entered
<blockquote> <pre>
    loco_1:    100   1.10   4  NA_2-6-2
</pre></blockquote>

A loco entry is composed of three fields:
the DCC address, the mph-to-DCC speed conversion factor and
the engine type name used for engine parameters.

The mph-to-DCC speed factor translates the speed
determined by the throttle to a DCC speed value.
DCC speed value typically from 0-128.
If a DCC speed of 128 corresponds to 40 mph
then the mph-to-DCC speed factor is 3.2 (128 / 40).

Then engine type can be the name of any of the names
of the engines in the engine parameter listing shown above.

"1234   2.5  NA_2-6-2" entered
<blockquote> <pre>
    loco_1:   1234   2.50   4  NA_2-6-2
</pre></blockquote>

"" entered
<blockquote> <pre>
    loco_2:    200   2.10   1  G-1sas
</pre></blockquote>

Additional locomotives could be configure at this point.

With this minimal set of parameters configured
the throttle should be able to connect to WiFi and JMRI, and
control the loco configured above.
These values should be saved.

"s" entered
<blockquote> <pre>
cfgSave: /spiffs/koala.cfg
    loco_2:    200   2.10   1  G-1sas
</pre></blockquote>

The configuration edit mode can be "quit" at this point.

"q" entered
<blockquote> <pre>
 cfgEdit: not saved
</pre></blockquote>

The "q" command does not automatically save parameters.

The modified configuration can be displayed for review.

"d" entered
<blockquote> <pre>
      name: my Throttle
      ssid: FiOS-DGHZ0
  password: my-password
  hostname: 192.168.1.227
      port:  12080
   locoIdx:      0
    loco_1:   1234   2.50   4  NA_2-6-2
    loco_2:    200   2.10   1  G-1sas
    loco_3:    300   3.10   2  K-1
    loco_4:    400   4.10   3  T-1
    loco_5:    500   3.20   4  NA_2-6-2
    loco_6:    600   2.20   5  BigBoy
    loco_7:    700   1.20   6  catskill
    loco_8:    800   2.30   7  MILW_4-4-2
    loco_9:    900   3.30   8  MILW_F-6
   loco_10:      0   0.00   0  I-10sa
     eng_0:  61.5  27.0  32.0  2 220 132 146  90  95.0  13.5  88.0   0.0   8.0 2-8-0      I-10sa
     eng_1:  80.0  25.0  28.0  2 200  90 140  90  95.0  19.0  80.0   0.0   8.0 4-6-2      G-1sas
     eng_2:  61.5  30.5  32.0  2 220 160 200 115 108.0  22.2 100.0   0.0   8.0 2-10-2     K-1
     eng_3:  70.0  27.0  32.0  2 240 126 200  90  95.0  13.5  88.0   0.0   8.0 4-8-4      T-1
     eng_4:  36.0  13.0  18.0  2 180  24  34   0   9.0  11.0  40.0  96.0   8.0 2-6-2T     NA_2-6-2
     eng_5:  68.0  23.8  32.0  4 300 270 380 170 150.0  18.0  95.0   0.0   8.0 4-8-8-4    BigBoy
     eng_6:  69.0  22.0  28.0  2 200   0   0   0   0.0   0.0   0.0   0.0   8.0 _          catskill
     eng_7:  84.0  19.0  28.0  2 300  74 140 123  69.0  19.0  80.0   0.0   8.0 4-4-2      MILW_4-4-2
     eng_8:  80.0  26.0  28.0  2 225  86 187 138  80.0  19.0  80.0   0.0   8.0 F-6        MILW_F-6
     eng_9:  84.0  23.5  30.0  2 300 108 207 187  96.5  19.0  82.5   0.0   8.0 F-7        MILW_F-7
    eng_10:  70.0  27.0  32.0  2 320 160 247 189 107.7   0.0   0.0   0.0   8.0 4-8-4      N&W
    eng_11:
loop: state 0x20 - ST_CFG
loop: state 0x00 -
</pre>
</blockquote>

The throttle should use the modified WiFi parameters
as soon as they are set.
The throttle will not connect to JMRI unless it is running
on the device with the specified IP and port parameters.
(port 12090 is also often used).

<!-- -----------------------------------------------------  ---------------- -->
<hr>
<p align=right>
<i>Greg Ciurpita - March 2021</i>
