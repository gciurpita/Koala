### Koala WiFi Throttle

<img width=300 align=right src=https://i.imgur.com/SMV6n7q.jpg>

Koala is a JMRI compatible WiFi throttle 
that implements more realistic control and behavior of a steam locomotive.
It computes the force, acceleration and speed of the train
based on control inputs,
not on decoder momentum.

It has separate controls for
<ul>
 <li> throttle,
 <li> reverser
(<a href=https://en.wikipedia.org/wiki/Johnson_Bar_(locomotive)>
Johnson Bar</a>),
 <li> independent brakes,
 <li> air brakes,
 <li> grade and
 <li> whistle quill (pitch)
</ul>

Speed is based on the application of Newton's Laws that combine
train mass, tractive effort, brake force, train resistance and grade.
The mass (weight) of the train, which affects acceleration,
is determined by weight and number of cars in a train
adjusted thru the menu.

Steam engine performance is optimized by using the reverser or
to reduce
<a href=https://en.wikipedia.org/wiki/Cutoff_(steam_engine)>cutoff</a>,
the percentage of the cylinder cycle the cylinder valve is open,
to maximize the extraction of energy of steam by allowing it to expand and
minimizing the consumption and reduction of steam pressure.

Brakes account for the filling of the brake line,
time depending on the
number of cars, brake line length and reservoir capacities.

The throttle is targeted to those interested in micro-operation,
the realistic operation of the locomotive and train,
but has options to simplify control.

<!-- ------------------------------------------------------  --------------- -->
---
<img src=https://i.stack.imgur.com/6ItJK.gif width=400 align=right>

#### Going Faster With Less Steam

The reverser is the arm leading to the left in the image below that the engineer can control that as shown causes the mechanics of the valve gear to cause the drivers to move forward or in reverse.   In the diagram, the reverser is moved between the extremes.   However, it can be positioned anywhere between those extremes

<p>
At the extremes, the cylinder valves are open the maximum amount of time during the cylinder cycle (~80%), allowing steam from the steam chest next to the cylinders to enter the cylinder during that time.   

<p>
At slow speeds and low steam flow rates, the cylinder steam pressure may only be slightly lower than the steam chest pressure and the steam chest pressure only slightly lower than the boiler pressure.   But at higher flow rates those differences are greater and the boiler pressure will be lower as steam is consumed quickly and boiler water is replenished at a higher rate.

<p>
Moving the reverser only portion a of it's extreme position causes the the cylinder valve to close before the end of the cylinder cycle (i.e. cutoff), filling the cylinder at ~ steam chest pressure for only a portion of the cycle

<p>
As a volume filled with some gas at pressure expands, the pressure ideally drops inversely proportionally with the volume (PV = nRT).   In other words, pressure doesn't drop to zero when the cylinder valve is closed.

<p>
<a href=https://en.wikipedia.org/wiki/Cutoff_(steam_engine)>
<img src=https://upload.wikimedia.org/wikipedia/commons/thumb/6/61/Indicator_diagram_steam_admission.svg/479px-Indicator_diagram_steam_admission.svg.png
width=400 align=right></a>

If the valve is closed at the halfway point during the cylinder cycle and the cycle allowed to continue, doubling the volume, the steam pressure ideally drops by half at the end of the cycle.   That means that during the later half cycle the average pressure is 75% of the max pressure.   And when considering that it was at full pressure for the first half of the cycle, the average steam pressure for the entire cycle is 87.5%.   In other words, using half as much steam only lowered the avg steam pressure by 12.5%

<p>
While this gain in efficiency is certainly helpful, the other aspect of using less steam, especially at speed, is that it provides time for steam to flow from the boiler into the steam chest, restoring pressure in the steam chest so that the maximum pressure at the beginning of each cylinder cycle is higher.

<p>
The combination of higher initial steam pressure and the relatively small loss in average pressure result in higher average force, allowing greater speed.

<p>
Knowing how to adjust the reverser as the locomotive gains speed, and avoiding slip, is challenging

<!-- ------------------------------------------------------  --------------- -->
#### Independent and Air Brakes

The independent brake pressure on the loco directly controls the brake, unlike the auto/air brake.   The brake force increases as the independent brake pressure increases.      suggest you try using the independent brakes with REL-Q(uick), REL-S(low), LAP, APP-S and APP-Q.  Last columns in output.

<p>
Auto/air brakes are like DCC in that the brake line both provides the impetus of the brakes, pressurizing the air reservoir in each car as well as signaling when to apply and release brakes.

<p>
Normal operation is to pressurize the brake line and reservoirs to 90 lb.

<p>
When the brake line pressure is allowed to drop (SVC or EMER), a valve in each car opens, allowing air from the reservoir to enter the brake cylinder applying pressure to the brakes (shoes).    Maximum pressure is when brake cylinder pressure is just 25 psi.

<p>
Setting the brakes to LAP, maintains the brake line and brake line pressure.    And allows a further decrease in brake line pressure and corresponding increase in brake cylinder pressure.

<p>
An increase of brake line pressure (REL position) causes the release of brake cylinder pressure and replenishment of reservoir.

<p>
So a single application of brakes may drop the brake line pressure from 90 to 65.   A slight increase in brake line pressure totally releases the brakes.  For example, back up to 70 psi.   A subsequent application further reduces the brake line and reservoir pressure to 45 psi,  and so on.

<!-- ------------------------------------------------------  --------------- -->
---
#### Downloading

The github repository contain the source code and documentation.
Click the green Code button above and select the Download ZIP to download.
Documentation in the Doc/ directory explains how to
install the Arduino IDE, ESP32 support,
build the code and program the board.

<!-- -----------------------------------------------------  ---------------- -->
<hr>
<p align=right>
<i>June 2022</i>
