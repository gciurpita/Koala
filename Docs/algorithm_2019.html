<title> A Steam Throttle Algorithm </title>

<table align=right>
 <tr> <td> Greg Ciurpita <br> May 2019
</table>

<h4> A Steam Throttle Algorithm </h4>

A steam throttle would add realism and
require more technical skill to operate model steam locomotive.
Rather than twisting a knob that dictates the speed of the engine,
a reverser lever adjusting cutoff and steam regulator (throttle)
need to be set appropriately
to prevent wheel slip when starting and
to conserve steam while running at speed.

<p>
Software in the throttle models steam locomotive behavior and
sends the corresponding speed to a model locomotive.
Parameters specific to a multiple locomotives can be stored.
Train parameters, tonnage or number of cars
is adjusted for appropriate behavior.
There is an assumption that the model is in continuous operation and
is not disrupted by derailment or dirty track,

<p>
The description of the algorithm is broken into several part.
They will be discussed in reverse order of operation
from basic physics to the steam model:
<ul>
 <li> <a href=#motion>physics of motion</a>
 <li> <a href=#drawbar>drawbar force</a>
 <li> <a href=#consumption>steam consumption</a>
 <li> <a href=#cylinder>cylinder pressure</a>
 <li> <a href=#boiler>boiler pressure</a>
</ul>

Some simulated results are shown at the end of these notes.

<p>
The throttle is expected to have the following controls and displays:
<ol>
 <li> steam regulator / throttle
 <li> reverser / Johnson bar
 <li> brake (# positions)
 <li> LCD display for programming and display of locomotive state
        such as boiler pressure, boiler water level, ...
 <li> buttons affecting LCD menus for programming loco and train parameters
 <li> possibly an LED
</ol>

The model for steam locomotive behavior is an estimate,
not a precise model of a steam locomotive.
It is accurate to the extent that improper use of the controls
will result in the loss of steam and reduction in speed of the locomotive.
Resulting time constants may not be accurate.

<!-- -----------------------------------------------------  ---------------- -->
<hr>
<a name=motion></a>
<h4> 1 Physics of Motion </h4>

Newton's law describe the motion of objects:
F = M &middot; A,
force equal mass time acceleration.
More precisely,
the throttle determines the forces on the train and
divides the mass by those forces to determine the acceleration.
The acceleration of the interval of time between iterations
determines the increase or decrease in speed of the train.

<p>
The mass of the train is determined from the weight of the train,
tonnage parameter, and
total weight of the locomotive and tender.
Their sum, (lbs)
is divided by the gravitational constant in imperial units, 32 ft/sec/sec,
to determine the mass in <i>slugs</i>.

<blockquote>
 <table width=300>
  <tr> <td> <i>mass <td> = <td> total_weight / 32.2
 </table>
</blockquote>

<p>
There are several forces to consider
<ul>
 <li> drawbar produced by the steam in the cylinders
 <li> resistance of the train 
 <li> brake forces applied to each car of the train
 <li> potentially the force of gravity both going up and down grades
</ul>

<p>
The acceleration is
<blockquote> <i>
acc = mass / (drawbar_force - train_resistance - brake_force - grade_force)
</blockquote> </i>

With the forces in <i>lbs</i> and the mass in <i>slugs</i>,
the acceleration is in ft/sec/sec.
From the value for acceleration and the time between iterations, <i>dT</i>,
the algorithm determines speed in both ft/sec and mph and RPM:

<blockquote>
 <table width=400>
  <tr> <td> <i>fps <td align=right> += <td> <i> acc * dT
  <tr> <td> <i>mph <td align=right> =  <td> <i> fps * 3600 / 5280
  <tr> <td> <i>RPM <td align=right> =  <td> <i> fps * 60 / (PI * driver_diameter / 12)
 </table>
</blockquote>

The RPM is used in determine steam consumption by the cylinders.
Speed in mph used to determine train resistance and
the value passed to the DCC command station
used to control the speed of the model locomotive.

<!-- -----------------------------------------------------  ---------------- -->
<hr>
<a name=drawbar></a>
<h4> 2 Drawbar Forces </h4>

Besides the force of the cylinders accelerating the train, 
train and locomotive resistance and brakes
will slow the train, and
grades can both slow or accelerate the train.

<!-- ---------------------------------  ---------------- -->
<a name=cylForce></a>
<h4> 2.1 Cylinder Force</h4>

<a href=Bin/sinF_w.gif>
<img src=Bin/sinF_w.gif height=150 align=right></a>

<a href=Bin/mep_w.gif>
<img src=Bin/mep_w.gif height=150 align=right></a>

Cutoff closes the valve to the cylinder to 
limit steam consumption and
take advantage of steam expansion.
Drawbar force depends on the mean effective pressure (MEP)
for various cutoffs
during the entire stroke of the cylinder
applied to driver wheel at various angles.

<p>
The plot at right shows that MEP is above 50%
for typical levels of cutoff
without accounting for other factors
such as changes in temperature or condensation.

<p>
The angle that cylinder force is applied to the driver must be accounted for.
The blue and red curves at right show the resulting force for each cylinder.
The green curve shows the combination of both cylinders on the driver and
the yellow curve the average.
While the peak value for each cylinder is 0.78 (&pi; / 4),
the average is ~1.0.

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

<a href=alco_pg20.jpg target="_blank">
<img src=alco_pg20.jpg height=200 align=right></a>

<a href=https://images.slideplayer.com/19/5861671/slides/slide_6.jpg
target="_blank">
<img src=https://images.slideplayer.com/19/5861671/slides/slide_6.jpg
height=200 align=right></a>

Bearing resistance in railway cars varies
from 2.3 to 19.8 lb/ton at 70 mph depending on whether the car
is empty or full.
Empty cars have greater resistance.
John Armstrong presents the graph at right in his book
<a href=https://www.amazon.com/Railroad-What-Does-Introduction-Railroading/dp/0911382585/ref=sr_1_1?keywords=armstrong+railroad&qid=1558787652&s=books&sr=1-1
target="_blank">
Railroad: What It Is, What It Does</a>

<p>
Two train parameters that may vary during operation are
number of empty and full cars.
Presumably it is easier to maintain the number of cars on a train
rather than their tonnage.
Nominal values for empty and full car weight can be stored.
Empty and full coal trains will have significantly different tonnage.
Armstrong' value can be used to determine the train resistance.

<p>
Values from the chart determine the total resistance of the train,
which increases as speed increases.

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

<p>
<i>It's not clear to what extent this may be implemented</i>


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



<!-- -----------------------------------------------------  ---------------- -->
<hr>
<a name=consumption></a>
<h4> 3 Steam Consumption </h4>

Steam consumption is the total amount of steam
allowed to enter the cylinders
during each update interval (&lt; 1 sec).
While cylinder volume is measured in cu.ft,
steam consumption is measured in pounds,
converted from cu.ft using the density of the steam (lb/cu.ft)
for the (cylinder) pressure using the saturated steam tables.

<p>
The steam volume per minute, <i>cu.ft</i>, is calculated using RPM,
the cutoff value that limits how long the cylinder valve is opened,
the number of cylinders (articulated engines have four) and
doubled because there are two cylinder strokes per revolution.
That rate is converted to weight per minute, <i>lb/min</i>,
from which the weight (lbs) 
is determined for the update period, <i>dTsec</i>.

<blockquote>
 <table width=400>
  <tr> <td> <i>volPmin <td> = <td> <i> rpm * cylVol * NstrPcyc * Ncyl * cutoff / 100
  <tr> <td> <i>lbPmin  <td> = <td> <i> vol * density(psi)
  <tr> <td> <i>lbSteam <td> = <td> <i> lbPmin * dTsec / 60 </i>
 </table>
</blockquote>

Steam consumption (lbs) is used both
to determine the residual amount of steam and hence, cylinder pressure, and
the boiler pressure after replenishment with an equal amount of feedwater.

<!-- ---------------------------------  ---------------- -->
<hr>
<a name=clinder></a>
<h4> 4 Cylinder Pressure </h4>

<a href=../../Images/sr_bruce.jpg target="_blank">
<img src=../../Images/sr_bruce.jpg height=200 align=right></a>

<a href=https://www.engineeringtoolbox.com/steam-flow-orifices-d_1158.html
target="_blank">
<img src=https://www.engineeringtoolbox.com/docs/documents/1158/steam-flow-orifices.png
height=200 align=right></a>

Steam flow through the steam regulator (throttle)
results in the cylinder pressure being less than the boiler pressure.
The 
<a href=https://www.engineeringtoolbox.com/steam-flow-orifices-d_1158.html
target="_blank">
Steam Flow - Orifices</a> 
chart relates the flow through an orifice
depending on the difference in pressure.

<p>
The residual pressure on the cylinder side of the steam regulator (throttle)
depends on a number of factors.
When not moving,
opening the throttle will fill the piping and cylinders
with steam at boiler pressure
causing the wheels to slip.
To limit this
until the wheels start moving and cylinders are
filled with steam later exhausted through the smoke stack,
the throttle must be open a small amount.

<p>
The drawing at right above from
<a href=https://www.amazon.com/Steam-Locomotive-America-Development-Century/dp/B000M1M2F8/ref=sr_1_1?keywords=bruce+steam+locomotive&qid=1559393093&s=books&sr=1-1
target="_blank">
The Steam Locomotive in America</a> by Bruce
shows a throttle composed of two slide valves: a pilot and main valve.
Their combined operation allows steam through a single small opening or
three larger openings.
Use of the smaller opening allow fine control when starting a locomotive.

<p>
The smaller throttle opening allows steam pressure to build up in the
piping and cylinders
until there is sufficient pressure to move the cylinder piston and drivers.
Once the cylinder pistons start moving
the volume occupied by the steam expands
which reduces steam pressure
but also allows more flow through the throttle.

<p>
Further opening of the throttle as the locomotive gains speed
allows the cylinder pressure to be controlled and
locomotive speed to gradually increase.


<!-- -----------------------------------------------------  ---------------- -->
<hr>
<a name=boiler></a>
<h4> 5 Boiler Pressure </h4>

Boiler pressure is directly related to steam and water temperature in the boiler
using the saturated steam tables.
That temperature depends on the number of BTUs
added to some weight of water and the amount of steam produced.

<p>
One BTU is the amount of heat required to raise one pound (lb) of water
one degree Fahrenheit.
970 BTU are required to evaporate one pound of liquid water to vapor.
Knowing the number of BTUs added to some amount of water at some temperature
determines the resulting temperature and amount of steam.

<p>
One way of viewing this is any quantity of water/steam
contains some number BTUs relative to some starting temperature.
This starting temperature could be the feedwater temperature.
In other words, feedwater has zero BTUs.

<p>
Replenishing the boiler with some amount of feedwater
means the boiler has lost some number of BTUs
corresponding to the replenishment amount.
But the number of BTUs is increased by the firing rate
from the burning fuel.

<p>
From the remaining BTU and firing rate,
an update steam temperature and pressure can be determined.


<!-- -----------------------------------------------------  ---------------- -->
<hr>
<a name=sim></a>
<h4> 6 Simulator and Results </h4>


<!-- -----------------------------------------------------  ---------------- -->
<hr>
<table width=100%> <tr> <td> </table>
