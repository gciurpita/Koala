<title>Description of Software and Hardware</title>
<h3>Description of Software and Hardware</h3>

<ul>
 <li> <a href=#swarch> Software Architecture
  <ul>
    <li> <a href=#config>  Configuration Parameters</a>
    <li> <a href=#menu>    Menu</a>
    <li> <a href=#keypad>  Keypad and Buttons</a>
    <li> <a href=#encoder>  Encoder and Potentiometer</a>
    <li> <a href=#pcread>   Pcread</a>
    <li> <a href=#motion>  Physics of Motion</a>
     <ul>
      <li> <a href=#steamEng> Steam Engine</a>
      <li> <a href=#brake>  Brakes</a>
     </ul>
  </ul>
 <li> <a href=#hardware> Hardware Prototype</a>
</ul>

<!-- ------------------------------------------------------  --------------- -->
<hr>
<table align=right>
  <tr> <td> June 2022
  <tr> <td> Greg Ciurpita
</table>

<a name=swarch></a>
<h4> Software Architecture </h4>

The throttle software is written primarily in C and
follows the basic Arduino model
of having <i>setup()</i> which runs once at startup and
<i>loop()</i> which runs repeatedly.
These routines are in <i>Koala.ino</i> 
which handles various modes of operating including

<blockquote>
 <table border=0 cellspacing=0>
  <tr><td> connecting to WiFi,
  <tr><td> connecting to JMRI,
  <tr><td> running the engine model, or
  <tr><td> running Design Verification Test (DVT) code
            which simply displays the control and keypad inputs
 </table>
</blockquote>

Numerous files are used to capture
various functionality and sub-functionality,
making it more easily located:

<blockquote>
 <table border=0 cellspacing=0 width=400>
<!--
   <tr><td> brakes.cpp   <td> air and independent brakes
   <tr><td> buttons.cpp  <td> translation of keypress to button value
   <tr><td> cfg.cpp      <td> handles parameters
   <tr><td> encoder.cpp  <td> encoder functions
   <tr><td> eng.cpp      <td> engine descriptions
   <tr><td> engine.cpp   <td> steam engine model functions
   <tr><td> file.cpp     <td> file and directory utilities
   <tr><td> keypad.cpp   <td> scans keypad matrix
   <tr><td> menu.cpp     <td> menu functions
   <tr><td> menus.cpp    <td> menu descriptions
   <tr><td> pcRead.cpp   <td> serial command interpreter
   <tr><td> physics.cpp  <td> application of Newton's Equations
   <tr><td> pots.cpp     <td> read potentiometers
   <tr><td> rollRes.cpp  <td> computer rolling resistance of cars
   <tr><td> utils.cpp    <td> miscellaneous functions
   <tr><td> vars.cpp     <td> all common variables
 -->

   <tr><td> encoder.cpp  <td> encoder functions
   <tr><td> pots.cpp     <td> read potentiometers

   <tr><td colspan=2> <hr>
   <tr><td> buttons.cpp  <td> translation of keypress to button value
   <tr><td> keypad.cpp   <td> scans keypad matrix

   <tr><td colspan=2> <hr>
   <tr><td> cfg.cpp      <td> handles parameters
   <tr><td> file.cpp     <td> file and directory utilities

   <tr><td colspan=2> <hr>
   <tr><td> menu.cpp     <td> menu functions
   <tr><td> menus.cpp    <td> menu descriptions

   <tr><td colspan=2> <hr>
   <tr><td> physics.cpp  <td> application of Newton's Equations
   <tr><td> brakes.cpp   <td> air and independent brakes
   <tr><td> eng.cpp      <td> engine descriptions
   <tr><td> engine.cpp   <td> steam engine model functions
   <tr><td> rollRes.cpp  <td> computer rolling resistance of cars

   <tr><td colspan=2> <hr>
   <tr><td> pcRead.cpp   <td> USB/Bluetooth serial command interpreter

   <tr><td colspan=2> <hr>
   <tr><td> utils.cpp    <td> miscellaneous functions
   <tr><td> vars.cpp     <td> all common variables
 </table>
</blockquote>

<!-- ------------------------------------------------------  --------------- -->
<hr>
<a name=config></a>
<h4> Configuration Parameters </h4>

<!-- ------------------------------------------------------  --------------- -->
<hr>
<a name=menu></a>
<h4> Menu </h4>

The code attempts to implement a   generic menu system
that allows any number of sub-menus, items within those sub-menus and
various options and types of options.
This requires that each menu element needs to identify its type,
a pointer to a sub-menu, the next item within an item and type of item, 
a boolean, integer, string.

<p>
While button presses can more obviously advance to the next sub-menu or item,
editing integers and strings is more tedious.
There are menu routines to scroll across a multi-digit value and
increment that digit, as well as
scroll across a string and select both capitalized and uncapitalized letters,
digits and special character, any possible ASCII character.
It is obviously tedious to use buttons to select one of over a hundred
possible characters.
In these edit modes, buttons have different purposes.

<p>
Also needed are stacks tracking the progression through the menu
easily allowing back up to the previous item.

<!-- ------------------------------------------------------  --------------- -->
<hr>
<a name=keypad></a>
<h4> Keypad and Buttons </h4>

The keypad routines supports at least 16 buttons.
It conventionally handles this by organizing the buttons in a matrix
or four rows and four columns,
requiring only eight I/O lines instead of 16.

<p>
The button routines map a keypress identified by row and column
to a specific value defined in a table.

<!-- ------------------------------------------------------  --------------- -->
<hr>
<a name=encoder></a>
<h4> Encoder and Potentiometer </h4>

The encoder and pot routines capture values for these devices
in global variables which are used wherever needed.
<i>AnalogRead()</i> is used to read the voltage across the pot.

<p>
An interrupt service routine (ISR) is used to recognize changes
in one of the encoder outputs,
reading the other input to determine the direction
which results in either incrementing or decrementing a position value.
The brake code tracks the range of positions
which along with position are unknown at startup.
The final design will limit the travel of the knob,
once both limits are reached, they should not change.

<!-- ------------------------------------------------------  --------------- -->
<hr>
<a name=pcread></a>
<h4> Pcread </h4>

<i>Pcread()</i> was developed for debugging
through the Arduino IDE serial monitor
but can be used generically with an serial application
including Bluetooth serial interfaces.
It will also be used to handle commands for setting parameters
that are set more tediously through the menu.

<p>
Commands are a single upper or lower case letter,
optionally preceded by a multi-digit decimal value.
Commands may simply change the value of variable or
invoke functions with arguments.

<!-- ------------------------------------------------------  --------------- -->
<hr>
<table align=right>
  <tr> <td> August 2022
  <tr> <td> Greg Ciurpita
</table>

<a name=motion></a>
<h4> Physics of Motion </h4>

Newton's 2nd law describes the motion of objects,
force equal mass times acceleration:
<blockquote>
acceleration = mass / force
</blockquote>

the acceleration, the change in speed of the train,
is the mass of the train divided by
the total force acting on the train.

<p>
The forces acting on the train include
<ul>
 <li> tractive effort, the tangential force produced by the drivers against the rails
 <li> train resistance
 <li> brake force applied to the locomotive and each car of the train, and
 <li> force of gravity due to grades
</ul>

<p>
There are various caveats to the application of these forces.
While the trains resistance and brake force can be non-zero at zero mph,
they cannot result in a negative acceleration and
cause the train to move backwards.
Grades can result in both positive and negative force.
Braking may be necessary on downhill grades to maintain speed.

<p>
The direction of the force is relative to the direction the train is facing,

<p>
Tractive effort depends on cylinder force and
the direction of the reverser.

<p>
The grade is comparable to tractive effort,
but added or subtracted from the tractive effort
such that the train will slow down or speed up
depending if the grade is ascending or descending.
The train can actually accelerate backward on an uphill grade,
slow down and possibly move backwards
if the force due to the grade is greater than the tractive force.

<p>
The rolling resistance is proportional to speed
but opposite the direction of motion (i.e opposite the sign of speed).
It is subtracted from the total force when moving forward and
added when moving rearwards.
It will become zero when speed is zero because it is proportional to speed.

<p>
The brake similar to rolling resistance, that braking force is opposite
the direction of motion.
Bear in mind there are both independent (locomotive) and air brakes, and
that there are no air brakes if there are no cars.

<blockquote><pre>
    force  = tractiveEffort
    force += gradeForce
    force -= rollingResistance * SGN(mph)

    if (brakeForce &gt; ABS(force))
        brakeForce = ABS(force))
    force -= brakeForce *SGN(mph)

</blockquote></pre>

<p>
The mass of the train is determined from the total weight of the train,
tonnage of all cars and
total weight of the locomotive and tender.
Their sum, (lbs)
is divided by the gravitational constant in imperial units, 32 ft/sec/sec,
to determine the mass in <i>slugs</i>.

<blockquote>
 <table width=300>
  <tr> <td> <i>mass <td> = <td> total_weight / 32.2</i>
 </table>
</blockquote>

where total_weight includes the cars, locomotive and tender.

<p>
The acceleration is
<blockquote> <i>
acc = mass / force
</blockquote> </i>

With the forces in <i>lbs</i> and the mass in <i>slugs</i>,
the acceleration is in ft/sec/sec.
From the value for acceleration and the time between iterations, <i>dT</i>,
the algorithm determines speed in both ft/sec and mph and RPM:

<blockquote>
 <table width=400>
  <tr> <td> <i>fps <td align=right> += <td> <i> acc * dT
  <tr> <td> <i>mph <td align=right> =  <td> <i> fps * 3600 / 5280
  <tr> <td> <i>rpm <td align=right> =  <td> <i> fps * 60 / (PI * driver_diameter / 12)
 </table>
</blockquote>
</i>

The RPM is used in determine steam consumption by the cylinders.
Speed in mph used to determine train resistance and
the value passed to the DCC command station
used to control the speed of the model locomotive.

<!-- ---------------------------------  ---------------- -->
<a name=te></a>
<h4> 1.1 Tractive Effort</h4>

The tractive effort (TE) is the force applied against
the rails turned by the cylinders.

<table> <tr> <td>

The force on the drivers
depends on the angle of the drivers.
The force is maximum
when the siderod connection to the driver
is perpendicular to the center of the driver and
is zero when in line with the center of the driver.

<p>
Typically there are two cylinders.
The driver connection points relative to the axle
are 90 degree apart,
so that when the force applied to the driver
is zero for one cylinder, it is maximum for the other
It is 60 degrees if there are three cylinders.
This is illustrated by the graph at right.

<p>
The red and blue curves represent the driver force
of each cylinder.
Using diameter instead of radius
The cylinder force is 78% relative to the cylinder diameter
(area = &pi; radius<sup>2</sup> / 2 = &pi; C<sup>2</sup> / 4
= 0.78 &middot; C<sup>2</sup>) (see below)

<p>
The green curve represents their sum.
The orange curves shows the average total force (green)
over time.
The average of the complete cycle is equal to the
maximum force applied by a cylinder,
~1 based on 78%.

<td valign=top>
<a href=Images/sinF_w.gif>
<img src=Images/sinF_w.gif height=150 align=right></a>
</table>


<p>
<a href=Images/mep_w.gif>
<img src=Images/mep_w.gif height=150 align=right></a>

Cutoff closes the valve to the cylinder to 
limit steam consumption and
take advantage of steam expansion.
Drawbar force depends on the mean effective pressure (MEP),
the average cylinder force as the cylinder piston
moves from one end of the cylinder,
where full cylinder pressure is applied,
through the point when cutoff occurs,
the cylinder valve is closed and
steam expands at reduced pressure
as the cylinder volume increases.

<p>
The MEP curve at right shows that MEP varies from 100 to 50%
depending on the amount of cutoff,
without accounting for other factors
such as changes in temperature or condensation.

<p>
The 
<a href=http://www.catskillarchive.com/rrextra/blclas.Html>
Tractive Force and Hauling Capability</a> page on the Catskill Archive
provides the following estimate for cylinder:

<blockquote>
  <img src=http://www.catskillarchive.com/rrextra/Image28.jpg>
</blockquote>

where
<blockquote>
 <table width=30%>
  <tr> <td> T  <td> = <td> tractive force at rail (lbs-force)
  <tr> <td> P  <td> = <td> boiler pressure (psi)
  <tr> <td> C  <td> = <td> cylinder diameter (in)
  <tr> <td> S  <td> = <td> cylinder stroke (in)
  <tr> <td> D  <td> = <td> driver diameter (in)
 </table>
</blockquote>

<p>
For two cylinders, the value of C<sup>2</sup> accounts
for the area of the cylinder pistons.
The force on the rail
depends on the ratio of
the radius of the siderod connection on the driver,
equal to ratio of the cylinder stroke and driver diameter
(S / D).

It appears that the factor of 0.85 accounts for various losses (15%).

<p>
<a href=https://en.wikipedia.org/wiki/Tractive_force#Steam_locomotives>
Steam Locomotive</a>
section of Tractive Force under wikipedia
mentions that value of 0.75 may also be used.
It further states that the value should be 
multiplied by 1.5 for a three cylinder and
by 2.0 for a four cylinder locomotive,
suggesting the value is for two cylinders.
This would be consistent with the plot and
value of 1.0 for a pair of cylinders 90 degrees apart,
accounting for additional losses.

<!-- ---------------------------------  ---------------- -->
<a name=resistance></a>
<h4> 2.2 Train Resistance</h4>

<a href=Images/alco_pg20.jpg target="_blank">
<img src=Images/alco_pg20.jpg height=200 align=right></a>

<a href=https://images.slideplayer.com/19/5861671/slides/slide_6.jpg
target="_blank">
<img src=https://images.slideplayer.com/19/5861671/slides/slide_6.jpg
height=200 align=right></a>

Bearing resistance in railway cars
depends on speed and whether car is empty or full.
It varies from
2.3 lb/ton at 10 mph to 10.4 at 70 mph for a full car and
4.5 to 19.8 for an empty car.
John Armstrong presents the graph at right in his book
<a href=https://www.amazon.com/Railroad-What-Does-Introduction-Railroading/dp/0911382585/ref=sr_1_1?keywords=armstrong+railroad&qid=1558787652&s=books&sr=1-1
target="_blank">
Railroad: What It Is, What It Does</a>

<p>
A steam locomotive has significantly more moving parts and
its resistance is higher.
Its value depends on the weight on its drivers.
From the table in the ALCO handbook above,
the locomotive resistance is calculated

<blockquote>
locoResistance (lb) = 25 * (1 + ton) + 0.26 mph<sup>2</sup>
</blockquote>

The resistance for the tender is assumed to be similar to a freight car.

<!-- ---------------------------------  ---------------- -->
<a name=brakes></a>
<h4> 2.3 Braking</h4>

<a href=https://ntsb.gov/news/events/Documents/2017_casselton_BMG_6_Casselton-Brake_Study.pdf
target="_blank">
Train Braking Simulation Study</a> (pg 65)
discusses Nominal Brake Ratio (NBR),
the ratio of braking force to loaded car weight.
It also mentions (pg 76) that NBR is 10% for the legacy car fleet and
that 14% is the maximum value.

<p>
A value of 10% of the loaded car weight will be used to determine
the maximum brake force of a train.
Some fraction of this will be used for the brake force
depending on the brake control.

<p>
That study also mentions that the propagation rate (pg 66) for air
down the length of the train is 950 ft/sec.
This suggests that a it takes ~5 sec for the brake signal,
a drop in air pressure,
to reach the last car of a 5000 ft train.
Furthermore,
<a href=http://www.railway-technical.com/trains/rolling-stock-index-l/train-equipment/brakes/electro-pneumatic-brakes-d.html
target="_blank">
Electro-Pneumatics Brakes</a> (under ECP)
mentions that the reduction in air pressure can take ~60 sec / 150 car.

<p>
<a href=http://www.oocities.org/picketfence/9549/hrbsw.html
target="_blank">
How Do Railway Braking Systems Work</a>
describes the brake control used
to drop brake line pressure using
<i>First Service, Service</i> and <i>Emergency</i> rates,
increasing brake line pressure using <i>Release</i> and <i>Running</i> and
<i>Lap</i> to maintain pressure.

<p>
Another consideration is that braking force cannot be gradually reduced.

<!-- ---------------------------------  ---------------- -->
<a name=grades></a>
<h4> 2.4 Grades</h4>

The force on a train going up or down a grade is the product
of the sine of the angle and the total weight of the train.
It is subtracted from the drawbar force when going up a grade,
but added to it when going down.

<p>
For small angles,
the sine of the angle is approximately the grade as a percent
(e.g. 1 ton for a 100 ton train up or down a 1% grade).



<!-- ------------------------------------------------------  --------------- -->
<hr>
<a name=brake></a>
<h4>Brakes</h4>

Koala brake code attempts to model Westinghouse air brakes.

<p>
An encoder input determines the brake one of several brake settings.
Multiple service settings represent 3 position
the brake may be set to within the service range
<ul>
 <li> Release
 <li> Running
 <li> Lap
 <li> Service-1
 <li> Service-2
 <li> Service-3
 <li> Emergency
</ul>

The Koala model primarily uses the brake setting to determine
a brake line fill rate (i.e. brkLnFlRat). 
The fill rate indicates the volume of air (cu.ft.) that the
brake valve is allowing to exit the brake line or
be filled from the compressor.

<p>
The brake line pressure depends on it volume as well as
the volume of the auxiliary reservoirs on all cars.
The brake line volume depends on the diameter of the brake line,
length and number of cars.

<p>
When brakes are applied (i.e. service) air is vented from the brake line.
The drop in brake line pressure causes the triple valve to 
allow air to flow from the auxiliary reservoir
into the brake piston cylinder.
When brakes are released,
air from the compressor enters the brake lines filling
both the brake lines and auxiliary reservoirs.

<p>
Air pressure (PSI) is estimated by determining the 
ratio the volume of air filling the volume of the brake line or
brake line and reservoirs.
There is both the unfilled volume of the lines and reservoir, and
the mass of air filling them.
It is assumed that a mass of air equal to the volume of a device
results in one atmosphere of pressure (14.7 PSI)

<p>
In Service mode, the fill rate is negative,
air is allows to exit the brake line.
<i>BrkLnFil</i> represents the mass of air in the line.
It calculated from the current brake line pressure.
If the pressure were 29.4 (2 atmosphere),
the mass of air, <i>brkLnFl</i> is estimated
to be twice the volume of the brake line. 
<i>BrkLnFl</i> is then adjust by the fill rate
for a specific amount of time

<pre>
    if (0 > brkFlRat)  {                          // dropping
        brkLnFil  = brkLnVol * brkLnPsi / AtmPsi;
        brkLnFil += brkFlRat * dMsec / 1000;        // filRate negative
</pre>

When Released, the fill rate is positive.
Similar to above,
the mass of brake line and reservoir air are estimated
based on the brake line pressure.
The total fill, <i>brkTotFil</i> is adjusted based on the fill rate and
the brake line fill, <i>brkLnFl</i> determined
as a proportion of the total volume.

<pre>
    else if (0 < brkFlRat)  {              // dropping
        brkTotFil  = (brkRsvrFil + brkLnVol) * brkLnPsi / AtmPsi;
        brkTotFil += brkFlRat * dMsec / 1000;       // filRate negative
        brkLnFil   = brkLnVol * brkTotFil / (brkRsvrFil + brkLnVol);
</pre>

Subsequent to either dropping or filling air into the brake line
the brake line pressure is calculated from the result
<pre>
        brkLnPsi  = AtmPsi * brkLnFil / brkLnVol;
</pre>

Limits are applied to values so that the fill amounts can never be 
less than zero or the brake line pressure greater than the maximum
pressure.

The actually amount of braking is calculated as a percentage (%)
of the maximum brake force, the nominal brake ratio (NBR)
which is assumed to be 10% of the gross weight of the car.

<p>
Since the brake line pressure is simply used to control
the triple valve connecting the auxiliary reservoir to the brake piston,
it is the change in brake line pressure that is used
to estimate the brake piston pressure.

<p>
The drop in pressure is calculated from the pressure
when last in in the Release or Lap brake setting, <i>brkLnPsi_0</i>
<pre>
    float dBrkLnPsi = brkLnPsi_0 - brkLnPsi;
</pre>

The brake percentage is simply a ratio of that difference.

<pre>
    if (0 < dBrkLnPsi)  {
        brakePct = BRK_PCT_COEF * dBrkLnPsi;
        brakePct = 100 < brakePct ? 100 : brakePct;
</pre>

There is no doubt room for improvement in the above model.
It is assumed to be "good enough".
Some possible weaknesses are that the fill rate when positive
probably depends on the difference in pressure
between the max pressure and current brake line pressure.
In other words it gets smaller as the brake line pressure
is closer to max.

<p>
It's also not clear if estimating the brake line pressure
from the air mass to device volume is accurate
but seems right based on the ideal gas law, PV/T.

<h4>Independent Brakes</h4>

My understanding is the independent brake handle
directly controls the flow of air
from the air reservoir in the locomotive
to the brake cylinders on the locomotive
as the triple valve does on cars.
Presumably there is a gauge indicating the cylinder pressure.
And presumably the brakes are released fully
just as the air brakes are.

<p>
Seems like a somewhat different algorithm is needed.

<!-- --------------  --------------- -->
<h4> Brake Table </h4>

The brake rates (cu.ft./min) can be adjusted in brakes.cpp.
there are separate values for recharge and discharge settings.   

<p>
<i>Self-lapping</i> means it automatically laps when the pressure has dropped a specific amount.    there are drop values (psi) for SVC 1 and 2.   current table values are 10 and 20, but i thought i read a value between 6-8 is more common for SVC 1.

<p>
Values are guesses, waiting for some expert advice

<blockquote><pre>
typedef struct {
    float rateRel;      // cu.ft. / min
    float rateSvc1;
    float rateSvc2;
    float rateSvc3;
    float rateEmer;
   
    int   dropSvc1;
    int   dropSvc2;

    const char* desc;
} Model_t;

Model_t models [] = {
    { 0.67, -0.85, -0.95, -1.05, -1.5, 10, 20, "self-lapping" },
    { 0.60, -0.85, -0.95, -1.05, -1.5,  0,  0, "non-self-lapping" },
};
</blockquote><p/re>

<i>Models []</i> is a table for different brakes (incomplete).
Rates probably depend on engine size and train length it's likely to pull.
These values may become scaling factors
with a max brake rate parameter stored along with engine parameters.

<!-- ------------------------------------------------------  --------------- -->
<a name=buttons></a>
<h4> Buttons </h4>

<table border=0 align=right> <tr><td>
<pre>
    { B_MODE, B_F3,   B_F7,   B_MENU },
    { B_F0,   B_F4,   B_F8,   B_SEL  },
    { B_F1,   B_F5,   B_F9,   B_UP   },
    { B_F2,   B_F6,   B_F10,  B_DN   },
</pre>
</table>

The sixteen buttons on both the protoboard and PCB
are arranged in a matrix but
on the final model may be arranged differently.

While both have the same ordering for rows, top to bottom,
the PCB board has column 1 on the left side like the schematic
but the proto board has column 1 on the right side.
The code describes the buttons 
<!-- ------------------------------------------------------  --------------- -->
<table width=100%> <tr><td> </table>
<hr>
<a name=steamEng></a>
<h4> Simulating a Steam Engine </h4>

There are several interesting aspects to simulating
the motion of a train pulled by a steam engine.
Of course, the most challenging is modeling the steam engine itself.

<p>
Brakes, both air and independent are interesting to model,
recognizing that air in a brake line is used to both
build up pressure in reservoir tanks in each car,
as well as control the filling of brake cylinders
from those tanks and releasing air from the cylinders.

<p>
Tying it all together are Newton's Laws of motion.
Newton's 2nd Law, F= ma, relates force (F), acceleration (a) and mass (m).

<p>
While the gas pedal on a car does control the speed of a car,
it doesn't dictate that speed.
It actually controls the force produced by the engine
which accelerates a car to speed.
The gas pedal is pressed farther toward the floor
when starting to accelerate the car quickly
than it is when maintaining the speed of the car.

<p>
There are four major forces affecting a train:
<dl> tractive effort (TE) produced by the engine
<dl> resistance of the train
<dl> brakes
<dl> grade

Of these four force, only two, TE and grade
can cause a train to move.
The other two, resistance and brake
must be overcome to cause motion.
In other words,
they are only a force when the train is moving.

<p>
Combining these four forces and
dividing that sum by the mass of a train
results in an acceleration
causing a train to either gain or lose speed.
Computing this speed and controlling a model
results in more realistic behavior.

<!-- ---------------------------------------------  ------------------------ -->
<table align=right>
  <tr> <td> August 2022
  <tr> <td> Greg Ciurpita
</table>

<h4> Steam Engine </h4>

Physics() needs the tractive effort generated by the engine,
returned from engineTe().
EngineTe() determines the fraction of a cylinder cycle, <i>st.cyc</i> 
from the previous cycle value, speed and
time delta since the previous iteration, and then calls cylinderPressure ().

<p>
CylinderPressure() attempts to model the flow of steam
from the steam chest into the cylinder and
to determine an effective cylinder force for that iteration.
The amount of steam flowing into the cylinder
both determines the actual cylinder pressure
as well as the consumption of steam from the steam chest
that affects the steam chest pressure.

<p>
While the approach below has several flaws and
can be substantially improved,
It results in a model where cutoff has a significant impact on performance.
If it didn't there would be little need for a reverser and
control over cutoff.

<p>
One oversight is neglecting the force on the backside of the cylinder
needed to force the steam out of the cylinder.
Incorporating this should improve the features of the model
but it is not obvious how to model this
since it requires modeling the resistance to flow through
the cylinder valve.

<p>
Steam in the steam chest is replenished from the boiler
through the throttle and piping.
The amount of steam flowing into the steam chest depends on
the difference in pressures and the resistance to flow
through the throttle.
(a more accurate model would also account for the resistance
of the piping.

<p>
At slow speeds,
cylinderPressure() computes the fraction of a cylinder cycle
change since the last iteration.
The cylinder pressure during the iteration is
equal to the steam chest pressure while the valve is open
if the cycle is less than the cutoff value or
it is proportional to the mean effective pressure 
when the valve is closed.

<p>
At higher speeds,
the cylinder pressure is computed as an average of
multiple and portions of cylinder cycles.

<p>
The number of cycles also determines steam consumption
based on the volume of the cylinder.
No attempt is made to determine the resistance to flow
through the valve,
the assumption is that
the cylinder and steam chest pressures are equal
when the cylinder valve is open.

<p>
With the cylinder valve open,
the volume occupied by the steam in both the steam chest
and cylinder grows as the cylinder cycles.
This causes the density to drop
from which the pressure can be determined using the steam tables.
(alternatively, the ideal gas law, PV/T could also determine an estimate).

<p>
After the cylinder valve has closed,
the mean effective pressure is determined
based on a linear reduction in pressure (PV/T)
as the cylinder volume increases.

<p>
Finally, the flow of steam through the throttle
is computed to determine the amount (lbs) of steam
replenishing the steam chest.
The difference between <i>st.consume</i>,
the amount of steam entering the cylinder and
<i>St.flow</i>, the amount of steam through the throttle,
updates <i>st.fill</i>, the amount of steam in the steam chest.

<h4> Throttle </h4>

Steam flow is assumed to be similar to Ohms Law,
that the flow is comparable to <i>current</i>,
which is proportional to the pressure difference, <i>voltage</i>  and
inversely proportional to the size of the opening, <i>resistance</i>.

<!-- ------------------------------------------------------  --------------- -->
<table width=100%> <tr><td> </table>
<hr> <hr>
<a name=hardware></a>
<h3> Hardware Prototype </h3>

The images below show the assembled prototype, board layout, ESP32 Wrover pins and
a schematic of the current design.
Note that the pinouts on the Wrover board are not sequential and
are labeled as the ESP32 chip pin they are routed to.

<p>
On the printed circuit board (PCB),
the pots along the bottom edge are, from left:
reverser, whistle quill (pitch), throttle and grade.
The encoders at top are air and on right edge is independent brakes.
An OLED display is attached to connector on left edge of board.

<p>
The switches on the PCB are not labeled consistent with the schematic.
SW0 is the top right, SW3 the top left and SW12, Menu, is bottom right.

<blockquote>
  <font face=Courier>
 <table border=0 cellspacing=0 width=300>
  <tr>   <td> B_F2     <td> B_F1     <td> B_F0     <td> B_MODE
  <tr>   <td> B_F6     <td> B_F5     <td> B_F4     <td> B_F3
  <tr>   <td> B_F10    <td> B_F9     <td> B_F8     <td> B_F7
  <tr>   <td> B_DN     <td> B_UP     <td> B_SEL    <td> B_MENU
 </table>
 </font>
</blockquote>

<table border=0 cellspacing=0 width=100%>
<tr>
 <td align=center>
  <a href=Images/IMG_1947a.jpg  target="_blank">
  <img src=Images/IMG_1947a.jpg height=250></a>

 <td align=center>
  <a href=Images/200828_pcb.png  target="_blank">
  <img src=Images/200828_pcb.png height=250></a>

 <td align=center>
  <a href=Images/wrover.jpg  target="_blank">
  <img src=Images/wrover.jpg height=250></a>

<tr><td colspan=3> &nbsp;
<tr><td colspan=3>
  <img src= Images/200828_schem.png width=100%>
</table>

<table width=100%></table>
<!-- ------------------------------------------------------  --------------- -->
<a name=history></a>
<h4> Development History </h4>

<ul>
 <li> Steam Locomotive Simulation (April 2019)
  <ul>
   <li> AWK model of steam locomotive physics,
            steam generation and cylinder force
   <li> <a href=https://github.com/gciurpita/steamThrottle target="_blank">
        github.com/gciurpita/steamThrottle</a>
  </ul>

 <li> Koala (4/5/20)
  <ul>
   <li> Bunza prototype
   <li> WiFi connectivity
   <li> menu & 4 buttons
   <li> JMRI connectivity
   <li> Bluetooth connectivity
   <li> throttle/reverser
   <li> control of loco on track via NCE USB adapter
  </ul>

 <li> Koala2 (6/21/20)
  <ul>
   <li> button matrix
   <li> attempt at brake input
   <li> problems using of TTGO-Koala
  </ul>

 <li> Koala3 (7/12/20)
  <ul>
   <li> purely serial control to avoid need for hardware interfaces
   <li> basic braking and physics controlling train speed
   <li> <a href=https://github.com/gciurpita/Koala3 target="_blank">
        github.com/gciurpita/Koala3</a>
  </ul>

 <li> DVT (8/15/20)
  <ul>
   <li> design, verification and test code
   <li> assess TTGO-Koala issues and re-allocation of pins
   <li> dual encoder input using interrupts
   <li> 4 analog inputs (throttle, reverser, whistle, grade)
   <li> button matrix
   <li> common pins.h
  </ul>

 <li> Koala 4 (9/19/20)
  <ul>
   <li> merge of DVT pin allocation and Koala 3 braking and physics
   <li> <a href=koala_0626.zip>Koala 0626.zip</a>
  </ul>
</ul>
