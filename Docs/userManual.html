<title>Koala WiFi Throttle</title>

<!--
<meta http-equiv=refresh content=5>
 -->

<table align=right>
 <tr> <td> May 17, 2022
      <br> Greg Ciurpita
</table>

<h3>Koala WiFi Throttle</h3>

<table> <tr><td></table>

Koala is a JMRI compatible WiFi throttle 
that implements more realistic control and behavior of a steam locomotive.
It implements steam locomotive throttle, reverser and brakes.
Speed is based on
tractive effort, train resistance, grade, brake force, train mass and
the application of Newton's Laws.
It will control corresponding sounds.
Koala is targeted to those interested in micro-operation,
realistic operation of a locomotive and train.

<p>
These notes discuss the design and potential design features of the throttle.

<ul>
 <li> <a href=#koala4>        Koala 4</a>
 <li> <a href=#install>       Installing ESP32 &amp; Koala</a>
 <li> <a href=#testing>       Testing the Throttle</a>
 <li> <a href=#startup>       Start up Operation</a>
 <li> <a href=#configuration> Configuration Parameters</a>
 <li> <a href=#cfgSerial>     Configuration Using Serial Interface</a>
 <li> <a href=#cfgOled>       Configuration Using OLED Display Menu</a>
 <li> <a href=#cfgMulti>      Layout Specific Configurations </a>

 <p>
 <li> <a href=#runtimeParams> Run Time Parameters</a>
 <li> <a href=#locoSelect>    Selecting Loco Address</a>
 <li> <a href=#jmri>          Configuring JMRI</a>
 <li> <a href=#wifi>          WiFi Parameters</a>
 <li> <a href=#pairing>       Pairing Bluetooth Device</a>

 <p>
 <li> <a href=#braking>       Braking</a>

 <p>
 <li> <a href=#hardware>      Hardware Prototype</a>
 <li> <a href=#history>       Development History</a>
 <li> <a href=#notes>         Notes</a>
</ul>

<!-- -------------------------------------------------  -------------------- -->
<hr>
<a name=koala4></a>
<h4>Koala 4</h4>

<a href=http://www.pacificsouthern.org/Members/GregCiurpita/Koala/Images/IMG_1947a.jpg>
<img width=300 align=right
 src= http://www.pacificsouthern.org/Members/GregCiurpita/Koala/Images/IMG_1947a.jpg></a>

Koala 4 completes a hardware design with all interfaces,
partially implements Westinghouse brakes and
a throttle controlling tractive effort.

The current design uses an
<ul>
 <li> <a href=http://www.lilygo.cn/prod_view.aspx?TypeId=50033&Id=1125
         target="_blank">TTGO-Koala ESP32</a> board.
 <li> 64x64 OLED display (hopefully 128x128),
 <li> rotary encoder for automatic (Westinghouse) brake control:
        release, lap, service, emergency
 <li> rotary encoder for independent brake control similar to automatic
 <li> potentiometer for throttles,
 <li> potentiometer for reversing and
 <li> 16 buttons for various operations: menu, light, sounds.
 <li> USB Type-C interface for reprogramming and diagnostics
</ul>


<p>
The display indicates start up progress,
operational state, loco address selection and
diagnostics.

<p>
Koala also supports USB serial (e.g. Arduino IDE), Bluetooth and Web Server
interfaces for control, configuration and potentially real-time performance.
Bluetooth interface requires a 
<a href=https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en_US
   target="_blank">Serial Bluetooth Terminal</a> and
is equivalent to the USB serial interface and
must be paired before using.
While the OLED display menu allows entry of all configurable parameters,
it will be tedious to edit numeric and alphanumeric values
one character or digit at a time.

<p>

The locomotive speed is not proportional to the throttle setting.
The throttle determines the fraction of maximum horsepower
used to accelerate the loco/train.
The horsepower and speed (mph) determines the tractive force and
along with the mass (weight) of the train,
determines the acceleration rate using Newton's Laws.
The accumulated acceleration determines the actual speed 
which is sent to the loco decoder via JMRI.

<p>
Automatic brakes are only partially implemented and
requires the ability to specify the number of cars or weight of the train.
Independent brakes have yet to be implemented, but
will be similar to automatic brakes without any delays and
based solely on the weight of the loco.

<p>
Westinghouse braking determines the brake force based on brake line pressure.
Maximum brake line pressure results in no braking
while reduced brake line pressure increases the brake force.
While brake line pressure can be further reduced to increase braking,
it cannot be partial decreased.
While the "lap" brake setting can maintain the current brake pressure,
the "release" setting causes an immediate suspension
of any braking in each car.

That brake force is similarly used to determine
the deceleration rate based on train mass and Newton's Laws.

<p>
The more realistic implementation of throttle to control
tractive effort and not simply as a speed selector and
the implementation of Westinghouse brakes
will require the user to operate a locomotive
more realistically.

<p>
Future plans include specifying locomotive parameters
to be used in determining operation.

<p><table width=100%> <tr> <td> <hr> </table>

<!-- --------------------------------------------  ------------------------- -->
<a name=install></a>
<h4>Installing ESP32 &amp; Koala</h4>

The throttle is based on Geoff Bunza's
<a href=https://forum.mrhmag.com/post/sma30-a-simplified-wifi-throttle-you-can-customize-12211948>
SMA30 A Simplified WiFi Throttle You Can Customize</a>
for an esp32 board,
using the esp32 tools and OLED library described within.

<p>
The Arduino IDE can be configured to support the ESP32.
<ul>
 <li> In the <b>File->Preferences->Additional Boards Manager URLs:</b> text bar
      enter <i>https://dl.espressif.com/dl/package_esp32_index.json</i>
</ul>

The Arduino IDE must then be configured for an ESP32:
<ul>
 <li> under <b>Tools->Board->ESP32 Arduino</b>
      select <i>ESP32 Wrover Module</i> (or appropriate board if different)
</ul>

The Koala throttle code also requires additional memory.
The partition must be changed
<ul>
 <li> under <b>Tools->Board->Partition Scheme</b>
      select <i>Minimal SPIFFS (1.9MB APP with OTA/190KB SPIFFS)</i>
</ul>
SPIFFS is Serial Peripheral Interface Flash File System.
OTA Over the Air programming.

<p>
At this point to open the Arduino IDE with the Koala code, either
<ul>
 <li> use <b>File->Open</b> to locate and select <i>Koala.ino</i>, or
 <li> select <i>Koala.ino</i> from a windows explorer window
      which should reopen the Arduino IDE
</ul>

The code can be compiled without loading
by selecting the &#10004; icon under <b>File</b> and
can be compiled/loaded
by selecting &rarr; icon under <b>Edit</b>.

<!-- --------------------------------------------  ------------------------- -->
<hr>
<a name=testing></a>
<h4>Testing the Throttle</h4>

<img width=300 align=right
 src= http://www.pacificsouthern.org/Members/GregCiurpita/Koala/Images/IMG_1426a.jpg>

When powered up,
the throttle attempts to automatically connect to WiFi and
then to a JMRI server.
This won't be possible if the WiFi SSID/password or
JMRI server IP address have not been configured.
Holding any button down during a reset will
abort connecting to WiFi and JMRI.

<p>
The device verification and test (DVT) mode can be entered
by pressing the button in the top-left corner (with upright display).
While in DVT mode,
the values of the throttle, reverser, grade and whistle are displayed,
along with pin values of both brake encoders and
a button values when pressed.
There may be no slope or grade devices connected.

<p>
From this state,
the menu buttons or serial interface can be used to configure Wifi and JMRI.
The ESP32 reset button can be used to restart.

<!-- --------------------------------------------  ------------------------- -->
<h4>Serial Configuration</h4>

(see Configuration Using Serial Interface below)

<p>
While a necessity,
using the OLED display and menu buttons to configure is tedious.
The USB/serial interface can be used to configure the unit.
Either the Arduino IDE serial monitor or a generic PC serial program
can be used.
A USB cable with a 
<a href=https://en.wikipedia.org/wiki/USB-C>
type-c connector</a> is needed.

<p>
The serial interface is serviced by a function, <i>pcRead()</i>,
intended for low-level debugging and has several sub-menus.
Entering "?" displays the current menu items.

<ul>
 <li> The initial menu controls pins.  Enter "m" to enter the <i>cmd</i> mode.
 <li> The cmd mode affects various throttle parameters.
        Enter "e" to enter the <i>cfg</i> mode
</ul>

The cfg mode sequentially displays each configurable item,
looping back to the first after the last is displayed.
Simply pressing the <i>enter</i> key skips to the next item.
Entering anything else replaces the current item.
Entering <i>q</i>, quits that mode, saving change items to memory.


<!-- -------------------------------------------------  -------------------- -->
<p><table width=100%> <tr> <td> <hr> </table>
<a name=startup></a>
<h4>Start-up Operation</h4>
Koala will display the following on start up:
<ul>
 <li> throttle name (e.g. Joe's Koala) and firmware version
 <li> display WiFi SSID and password and repeatedly attempt to connect
 <li> display JMRI host and port and repeatedly attempt to connect
 <li> display time and loco address or "No Loco"
</ul>

Koala will repeatedly attempt to connect to WiFi or JMRI.
It will fail to connect if
valid parameters are not configured, WiFi is not active or
JMRI Panel Pro is not running.

<p>
The display will indicate the WiFi and JMRI parameters
when attempting to connect.
Holding down any(?) button will abort attempts
to connect to WiFi and/or JMRI,
allowing the OLED display menu or serial interfaces to run
so that correct WiFi/JMRI parameters can be set.
<b>Any Bluetooth device needs to be paired with the Koala Throttle.</b>

The WiFi and JMRI parameters can be set
using any of the interfaces.
All parameters, once set are stored in EEPROM and
are retrieved automatically on start up:

<p>
 <table border=1 cellspacing=0 width=200 align=right>
  <tr> <th colspan=2> Configuration Parameters
  <tr> <td align=left> WiFi SSID      <td> string
  <tr> <td align=left> WiFi password  <td> string
  <tr> <td align=left> JMRI hostname  <td> string
  <tr> <td align=left> JMRI port      <td> numeric
  
  <tr> <td align=left> throttle name  <td> string
  
  <tr> <td align=left> loco address 0 <td> numeric
  <tr> <td align=left> loco address 1 <td> numeric
  <tr> <td align=left> loco address 2 <td> numeric
  <tr> <td align=left> loco address 3 <td> numeric
  <tr> <td align=left> loco address 4 <td> numeric
  <tr> <td align=left> loco address 5 <td> numeric
  <tr> <td align=left> loco address 6 <td> numeric
  <tr> <td align=left> loco address 7 <td> numeric
  <tr> <td align=left> loco address 8 <td> numeric
  <tr> <td align=left> loco address 9 <td> numeric
 </table>

<p>
It is also suggested to set up to ten loco DCC addresses.
Once they are set,
any one of the available addresses can be selected
relatively easy using the OLED display menu and button interface.
Any of the ten loco addresses can be edited at a later time
using either interface.

<!-- -------------------------------------------------  -------------------- -->
<a name=configuration></a>
<h4>Configuration Parameters</h4>

The table at right is the current list of configurable parameters.
It is expected that
the list of configurable parameters will grow substantially.

<p>
The parameters are operated on by the following interfaces.
Each of these interfaces will automatically operate
on any new parameters as they are added.

<ul>
 <li> the OLED display menu
 <li> USB serial interface
 <li> Bluetooth serial interface
 <li> web page
</ul>

<p>
The USB and serial interfaces
sequentially prompt the user with each parameters and its values.
The enter key without any preceding text 
simply skips updating the parameter.
The parameter is updated with any text that is entered.
The first entry is repeated after the last entry.

<p>
The Web page interface provides a table with boxes
showing parameter values that can be edited.
But the web page interface is still pretty crude.

<!-- -------------------------------------------------  -------------------- -->
<a name=cfgSerial></a>
<h4>Configuration Using Serial Interface </h4>

The serial interface accessible as a com port on a PC
provides a less tedious way of editing configuration parameters.
It can be accessed using the <i>Tools->Serial Monitor</i>
from the Arduino IDE or thru a Windows terminal emulator program.

<ul style="list-style-type:none">
 <li> - enter "?" to figure out what mode
 <li> - if pin mode, enter "m"
 <li> - from cmdMode, enter "e"
 <li> - in cfgMode scroll thru values, enter key to skip to next
 <li> _ enter new text for those that need to change
 <li> _ scroll thru again to make sure the new values are taken
 <li> _ enter "S" to save
 <li> _ enter "q" to quit back to cmdMode
</ul>

<!-- -------------------------------------------------  -------------------- -->
<a name=cfgOled></a>
<h4> Configuration Using OLED Display Menu </h4>

The following (attempts to) describe how to
edit WiFi and JMRI parameters using the OLED display menu.

<p>
<blockquote>
<table border=1 cellspacing=0 width=100%>
<tr>
<td valign=top width=33%>

When started, the name of the throttle and version on displayed for two second
<blockquote>
Koala Throttle
<br> 200411c
</blockquote>

It next attempts to connect to the Wifi Router,
displaying the WiFi SSID and password strings.

<blockquote>
WiFi connecting
<br> wifi-ssid
<br> wifi-password
</blockquote>

Holding the any button down will abort the WiFi connect.
Otherwise the screen will display the following for five seconds
<blockquote>
configure
<br> WiFi &amp; JMRI
<br> Parameters
</blockquote>

It then displays the main screen
which indicates the time in use,
"No Loco" since no loco address has been selected and
the first menu screen, "Loco" "Addr"
<blockquote>
1:30    No Loco
<br>
<br> Loco
<br> Addr
</blockquote>

The Up and Dn buttons move thru the menu
Pressing Up once should display
<blockquote>
1:30    No Loco
<br>
<br> Comm
<br> Cfg
</blockquote>

<!-- ---------------------------------------- -->
<td valign=top width=33%>
Pressing the Sel button displays the JMRI hostname
<blockquote>
1:30    No Loco
<br>
<br> Host
<br> 192.168.1
</blockquote>

Pressing the Sel button again displays the hostname
with a arrow "^" indicating the character to be edited
using the Up and Dn buttons
<blockquote>
1:30    No Loco
<br>
<br> 192.168.1
<br> ^
</blockquote>

Pressing the Sel button again moves the arrow to the right
<blockquote>
1:30    No Loco
<br>
<br> 192.168.1
<br> &nbsp;^
</blockquote>

The Sel button will move the arrow past the last character
so that additional characters can be added.
<blockquote>
1:30    No Loco
<br>
<br> 192.168.1
<br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;^
</blockquote>

To delete the last character, replace it with a space

<!-- ---------------------------------------- -->
<td valign=top>
<p>
Press the Menu button to capture the changes
<blockquote>
1:30    No Loco
<br>
<br> Host
<br> 192.168.174
</blockquote>

Press the Up button to move to the next menu entry, the JMRI Port number.
It can similar be edited by pressing the Sel button
to select the entry for editing, moving the cursor,
using the Up and Dn buttons to change the digit and
the Menu button to capture the value.
<blockquote>
1:30    No Loco
<br>
<br> Port
<br> 12080
</blockquote>

At the menu level, the next menu item is the WiFi SSID
which can be edited similar to the JMRI host name
<blockquote>
1:30    No Loco
<br>
<br> SSID
<br> WiFi-ssid
</blockquote>

The next menu item is the WiFi password which can similarly be edited
<blockquote>
1:30    No Loco
<br>
<br> SSID
<br> WiFi-ssid
</blockquote>

Once all the wifi parameters are changed reset the throttle
</table>
</blockquote>

<!-- -------------------------------------------------  -------------------- -->
<a name=cfgMulti></a>
<h4> Layout Specific Configurations </h4>

Storing multiple SSID/passwords in EEPROM are being considered.
Multiple SSID/passwords would make it convenient to return
to a layout previously operated on.
Each available SSID/password would be sequentially used
while attempting to connect to WiFi.

<p>
Using the successful SSID/password as a key,
separate configurations could be retrieved for different layouts.

<p>
It would save time when operating on a new layout
to pre-configure the throttle with the
SSID/password, loco addresses and parameters.

<p>
Bulk configuration is being considered
by sending a command file to the throttle serial interface.
The user would format a configuration description file
using notepad or wordpad
which a steam throttle app on a laptop would verify and
translate into a command file.
The command file would be processed
using either the USB or Bluetooth serial interface
as if the configuration were entered manually.

<!-- -------------------------------------------------  -------------------- -->
<hr>
<a name=runtimeParams></a>
<h4>Run Time Parameters</h4>

Run time parameters are not stored in EEPROM and
represent the state of the emulation.

 <table border=1 cellspacing=0 width=150 align=right>
  <tr> <th colspan=2> Run Time <br> Parameters

  <tr> <td align=center> brake
  <tr> <td align=center> brakeInd
  <tr> <td align=center> brakePct
  <tr> <td align=center> brakeCfm
  <tr> <td align=center> cars
  <tr> <td align=center> carLen
  <tr> <td align=center> dir
  <tr> <td align=center> dirLst
  <tr> <td align=center> loco
  <tr> <td align=center> mph
  <tr> <td align=center> mass
  <tr> <td align=center> reverser
  <tr> <td align=center> state
  <tr> <td align=center> throttle
  <tr> <td align=center> tractEff
  <tr> <td align=center> tractEffMax
  <tr> <td align=center> timeSec
  <tr> <td align=center> tonnage
  <tr> <td align=center> wtCar
  <tr> <td align=center> wtLoco
 </table>

At right is a list of run time parameters
that can be displayed on the serial interfaces
for diagnostic purposes.

However, some parameters, the number of cars on the train,
need to be adjusted during operation.
Not only would this be tedious for the operator 
through the OLED display menu,
it may be too distracting.
Thoughts are a conductor assistant can update parameter
in unison with the engineer
through the Bluetooth interface.

<!-- -------------------------------------------------  -------------------- -->
<a name=locoSelect></a>
<h4>Selecting Loco Address</h4>

<ol>
 <li> press the MENU button to display the first menu option which is loco selection
 <li> press the SEL button to select that option
 <li> press the UP/DN buttons to scroll thru the list of loco addresses
 <li> press the SEL button to select a particular loco address
 <br> at this point the loco address can be edited
      similar to how the IP address described above is edited
 <li> press the MENU button to select that loco address
</ol>

<!-- -------------------------------------------------  -------------------- -->
<a name=numCars></a>
<h4> Number of Cars / Tonnage</h4>

The number of cars or tonnage is used to determine the mass
of the train which affects acceleration.
It does not affect deceleration because each car has brakes
and braking force is proportional to the number of cars.

<p>
The number of cars also affects the length of the brake line
which will affect the time to change brake line pressures.
Reducing brake line pressure will be faster than
increasing brake line pressure.
Reducing pressure simply requires reducing the amount of air
in the brake line.
Increasing pressure requires refilling brake reservoirs on each car
in additional to re-pressurizing the brake line itself.


<p>
The number of cars is a convenient way to estimate tonnage
based on a default value for a car weight.
A mix of cars can implemented by specifying a car weight
that is varies between its empty and loaded weight
proportional to number of fully loaded cars.

<p>
The number of cars can be currently configured using a serial interface.
It is expected that two buttons will be allocated to +/- the number of cars.
It is expected that the number of cars will change when switching cars.

<!-- ------------------------------------------------------  --------------- -->
<hr>
<a name=jmri></a>
<h4> Configuring JMRI Panel Pro WiThrottle Server</h4>

<ul>
 <li> Start JMRI PanelPro
 <li> select a profile
 <li> select Edit->Preferences
 <li> select WiThrottle from list on left
 <li> specify 12080 as Port Number
 <li> check Start automatically with application
 <li> from Preferences, select Connections and complete for DCC interface used

 <li> add cabling to connect USB port to DCC system interface
 <li> make sure DCC system is powered on
</ul>

<!-- ------------------------------------------------------  --------------- -->
<a name=wifi></a>
<h4> WiFi Parameters </h4>

Connecting to WiFi requires an SSID
which is a name given to a WiFi device and password.
Clicking the WiFi icon on a laptop or phone
will often list one or more nearby WiFi devices.
WiFi devices in homes often require a password.
Koala requires the SSID and password of the WiFi device 
in order to connect through it to the JMRI device.

<p>
Future plans are to potentially save multiple SSID/passwords
that are sequentially scanned
allowing Koala to be used on multiple layouts
without needed to re-enter parameters each time.

<!-- ------------------------------------------------------  --------------- -->
<a name=pairing></a>
<h4> Pairing Bluetooth Device </h4>

TBD - it think it will be useful to explain how to pair a
<a href=https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en_US
   target="_blank">Serial Bluetooth Terminal</a> 
with Koala.

<!-- ------------------------------------------------------  --------------- -->
<!-- ------------------------------------------------------  --------------- -->
<hr>
<h3> Operator's Manual </h3>

<a name=braking></a>
<h4> Braking</h4>

<table border=1 cellspacing=0 align=right>
 <tr> <th> Air <th> Independent
 <tr> <td align=center> Release   <td align=center> Release
 <tr> <td align=center> Running   <td align=center> Running
 <tr> <td align=center> Lap       <td align=center> Lap
 <tr> <td align=center> Service-1 <td align=center> Slow-Application
 <tr> <td align=center> Service-2 <td align=center> Quick-Application
 <tr> <td align=center> Emergency <td align=center> E-Stop
 <tr> <td align=center> E-Stop    <td align=center> &nbsp;
</table>

Since there are brakes on each car,
the deceleration rate of the train depends
primarily on the % brake determined by the brake line pressure.
The train should stop in the same amount of time
for the same % brake regardless of # of cars (ignoring engine).

<p>
The maximum (100% brake) nominal brake rate (NBR) is 10% of the car weight.

<p>
Of course, while % brake determines how quickly a train stops,
the brake setting (cu.ft./min) determines
how quickly the desired % brake is attained.

<p>
For the same SVC setting,
it will take longer on a longer train to reduce the brake line pressure
because there will be more air in the brake line.
It will take longer to reach a specific % brake on a longer train
which will delay stopping the train.


<p>
<blockquote>
<img src= http://www.pacificsouthern.org/Members/GregCiurpita/Koala/Images/brakeRate.png>
</blockquote>


<!-- ------------------------------------------------------  --------------- -->
<hr>
<h3> Nuts & Bolts (How Things Work) </h3>

