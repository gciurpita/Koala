<title>Steam Throttle - Theory of Engine & Brakes Simulation</title>

<table align=right> <tr> <td>
September 2022 <br> Greg Ciurpita
</table>

<h3>Steam Throttle - Theory of Engine & Brakes Simulation</h3>

<ul>
 <li> <a href=#going>  Going Faster With Less Steam</a>
  <ul>
   <li> <a href=#iterRate>   Iteration Rate</a>
   <li> <a href=#cutVsTmg>   Cutoff vs Valve Timing </a>
   <li> <a href=#cylPress>   Combined Cylinder Pressures </a>
   <li> <a href=#cylTorque>  Cylinder Force vs Side-rod Angle </a>
   <li> <a href=#cylPeaks>   Cylinder Force Peaks </a>
   <li> <a href=#consump>    Steam Consumption vs Supply </a>
  </ul>
 <li> <a href=#brakes>  Brakes: Air and Independent </a>
 <li> <a href=#callFlow>    Code Call Flow</a>
</ul>


<!-- ------------------------------------------------------  --------------- -->
<hr>
<a name=going></a>
<h4>Going Faster With Less Steam</h4>

<img src=https://i.stack.imgur.com/6ItJK.gif width=400 align=right>

The reverser is the arm leading to the left in the image below that the engineer can control that as shown causes the mechanics of the valve gear to cause the drivers to move forward or in reverse.   In the diagram, the reverser is moved between the extremes.   However, it can be positioned anywhere between those extremes

<p>
At the extremes, the cylinder valves are open the maximum amount of time during the cylinder cycle (~80%), allowing steam from the steam chest next to the cylinders to enter the cylinder during that time.   

<p>
At slow speeds and low steam flow rates, the cylinder steam pressure may only be slightly lower than the steam chest pressure and the steam chest pressure only slightly lower than the boiler pressure.   But at higher flow rates those differences are greater and the boiler pressure will be lower as steam is consumed quickly and boiler water is replenished at a higher rate.

<p>
Moving the reverser only portion a of it's extreme position causes the the cylinder valve to close before the end of the cylinder cycle (i.e. cutoff), filling the cylinder at ~ steam chest pressure for only a portion of the cycle

<p>
<a href=https://en.wikipedia.org/wiki/Cutoff_(steam_engine)>
<img src=https://upload.wikimedia.org/wikipedia/commons/thumb/6/61/Indicator_diagram_steam_admission.svg/479px-Indicator_diagram_steam_admission.svg.png
width=400 align=right></a>

As a volume filled with some gas at pressure expands, the pressure ideally drops inversely proportionally with the volume (PV = nRT).   In other words, pressure doesn't drop to zero when the cylinder valve is closed.

<p>
If the valve is closed at the halfway point during the cylinder cycle and the cycle allowed to continue, doubling the volume, the steam pressure ideally drops by half at the end of the cycle.   That means that during the later half cycle the average pressure is 75% of the max pressure.   And when considering that it was at full pressure for the first half of the cycle, the average steam pressure for the entire cycle is 87.5%.   In other words, using half as much steam only lowered the avg steam pressure by 12.5%

<p>
While this gain in efficiency is certainly helpful, the other aspect of using less steam, especially at speed, is that it provides time for steam to flow from the boiler into the steam chest, restoring pressure in the steam chest so that the maximum pressure at the beginning of each cylinder cycle is higher.

<p>
The combination of higher initial steam pressure and the relatively small loss in average pressure result in higher average force, allowing greater speed.

<p>
Knowing how to adjust the reverser as the locomotive gains speed, and avoiding slip, is challenging

<!-- ----------------------------------  --------------- -->
<a name=iterRate></a>
<h4> Iteration Rate </h4>

<table align=right> <tr> <td>
<pre>
          36.0   48.0   60.0   72.0   84.0 diaIn
           4.7    6.3    7.9    9.4   11.0 circFt/2
    fps fraction of cycle
      5   0.11   0.08   0.06   0.05   0.05
     10   0.21   0.16   0.13   0.11   0.09
     15   0.32   0.24   0.19   0.16   0.14
     20   0.42   0.32   0.25   0.21   0.18
     25   0.53   0.40   0.32   0.27   0.23
     30   0.64   0.48   0.38   0.32   0.27
     35   0.74   0.56   0.45   0.37   0.32
     40   0.85   0.64   0.51   0.42   0.36
     45   0.95   0.72   0.57   0.48   0.41
     50          0.80   0.64   0.53   0.45
     55          0.88   0.70   0.58   0.50
     60          0.95   0.76   0.64   0.55
     65                 0.83   0.69   0.59
     70                 0.89   0.74   0.64
     75                 0.95   0.80   0.68
     80                        0.85   0.73
     85                        0.90   0.77
     90                        0.95   0.82
     95                               0.86
    100                               0.91
    105                               0.95
</pre>
</table>

How quickly does user input need to be recognized and
how frequently does the simulation need to be updated
to respond to used input?
Human response is about 20 ms
(consider articulated phonemes during speech).
A throttle update time of 0.1 sec is probably imperceptable.

<p>
The NA 2-6-2 has small 36" diameter drivers with a circumference of 9.4 ft.
A cylinder cycle completes every half revolution or every 4.7 ft.
The loco traveling 47.1 fps (32 mph)
would complete one cylinder cycle in 0.1 sec.
Only a fraction of a cylinder cycle would complete every 0.1 sec
at lower speeds.
The cylinder would move just a fraction of a cycle at most speeds.

<p>
Larger drivers require higher speeds to complete a cylinder cylinder 
in 0.1 sec.
The table shows the fraction of a cylinder cycle every 0.1 sec
for a range of driver diameters and speeds.

<table width=100%> <tr> <td> </table>
<!-- ----------------------------------  --------------- -->
<a name=cutVsTmg></a>
<h4> Cutoff vs Valve Timing </h4>

<img src=Images/cutoffTmg.png width=400 align=right>

At startup,
it's possible that only one cylinder valve is open,
requiring the loco to start with just one cylinder,
even with the reverser pushed to the extreme.
The diagram illustrates the timing of both cylinder valves
at 20, 40, 60 and 80% cutoff.
Even at 80% cutoff,
there are driver positions where on one value is open.

<p>
Since there is nothing to prevent
being at one of these positions when stopping,
the simulation must support this and
this is yet another nuance of operating a steam locomotive

<p>
At lower cutoff settings,
the tractive effort will be bursty (not smooth).
This burstyness may not be very perceptible,
but during startup, could more easily lead to slip,
which the user needs to be careful to avoid.

<p>
Finally,
the simualation needs to consider the valve timing
when determining the flow of steam into the steam chest
resulting in the steam pressure during the next cylinder cycle.
The steam flow from the boiler is divided between the cylinders
but will be greater to the steam chest with less pressure.
This of course equalizes the pressures,
but accurately determining the steam chest pressure
is essential to providing a purpose for modeling cutoff.


<table width=100%> <tr> <td> </table>

<!-- ----------------------------------  --------------- -->
<a name=cylPress></a>
<h4> Combined Cylinder Pressures </h4>

<img src=Images/cylsPsi.png width=400 align=right>

the following shows the summed cylinder pressures (red) the left and right cylinder pressures in yellow/cyan.   the cylinder cycles (ramps) yellow/cyan at the bottom and the delta cycle / iteration just above (what looks like a step function).

<p>
this doesn't consider the drop in steam chest pressure due to consumption which i believe would be an issue at speed.   not sure that even at low speeds it needs to be considered

<p>
hope it's clear that the individual cylinder pressure (yellow/cyan) is close to steam chest pressure (equal in this sim) while the cylinder valve is open (therefore flat) and then drops (~1/log) when the valve is closed and steam expands.   the summed steam pressure (red) is a bit funky and needs work but illustrates the fluctuations in pressure that are possible (a cutoff of 20% at such low speed is unlikely)

<p>
the speed, fps, is increased at various points, 1, 5, 60 and some crude logic added to compute cylinder pressure depending on if dCyc > 1.  while cutoff is 80 for first iteration, it is dropped to 20% afterwards

<p>
presumably at slow speed, a fraction of a cylinder cycle, cylinder pressure can vary from iteration to iteration.   no doubt averaged out by the mass of the train

<p>
i think neglecting that there are 2 cylinders significantly reduced the tractive force.  i think that plus accounting for cylinder pressure variation at low speed could result in slip occurring more easily and this may address Mark's concern.

<!-- ----------------------------------  --------------- -->
<a name=cylTorque></a>
<h4> Cylinder Force vs Side-rod Angle </h4>

<p>
but i've just been looking at the effect on torque and also realized i should probably average the cylinder pressure between 2 iteration.     the effect on torque needs to consider the angle of the side rod on the wheel.   this could be simplified when dCycl >= 1, but that is at speed > 30 mph

<p>
<table align=right> <tr> <td>
<pre>
  18  0.309   10 %      ^      ^      ^      ^
  36  0.588   20 %      ^      ^      ^      ^
  54  0.809   30 %   0.67      ^      ^      ^
  72  0.951   40 %   0.50      ^      ^      ^
  90  1.000   50 %   0.40   0.80      ^      ^
 108  0.951   60 %   0.33   0.67      ^      ^
 126  0.809   70 %   0.29   0.57   0.86      ^
 144  0.588   80 %   0.25   0.50   0.75      ^
 162  0.309   90 %   0.22   0.44   0.67   0.89

                     4.66   6.98   8.27   8.89 avg force
                     3.08   4.98   5.95   6.28 avg torque
</pre>
</table>

1st column is the angle of the driver (yes, each cycle is half a rotation)
<br> 2nd column is sine of the angle
<br> 3rd is % of cycle
<br> 4th is (mean) effective pressure. full (^) pressure if valve open for 20% cutoff
<br> 5th-7th column are for 40, 60 & 80% cutoff

<p>
i hope you see i'm still just trying to get a feel, make sure all the significant factors are being considered (e.g. 2 cylinders, torque arms, ratio of wheels to side-rod position on driver, ???)


<p>
the 2nd to last row reports the simple sum (incorrectly states avg) of of the forces over the entire cycle
the last row accounts for sin.
there's a greater avg force if pressure is large at the half cycle, 90 deg

<p>
these avgs would only apply at > "slow speed".    i think the force at a fraction of a rotation at slow speed needs to be accounted for.  may need to determine avg torque (not just force) between last and current iteration until beyond "slow speed" where some avg torque / cycle can be used

<p>
presumably this make operating more involved, which is presumably what the "micro-operator" desires

<p>
of course these don't account for the consumption of steam and steam chest pressure at speed, hence the "^" to indicate whatever that is.  that computation is separate as needs to account for back pressure as well

<!-- ----------------------------------  --------------- -->
<a name=cylPeaks></a>
<h4> Cylinder Force Peaks </h4>
 <img src=Images/cylPeaks.png width=400 align=right>


the next concern is determining the avg force for that change in cycle %.   the following illustrates the side-rod force, cylinder PSI and accounting for side-rod angle relative to the driver.    it shows how the side-rod force peaks but depending on cutoff which results in decreasing PSI beyond the cutoff point, that peak can be nearer the beginning of the cycle instead of the halfway point where the side-rod is at 90°.

<p>
averaging the force due to the current and previous cycle may result in a less accurate value if the peak is between those two points.   it therefore seems necessary that case to also include the peak value in the average

<p>
the expectation is that engine.cpp/h can be replaced with a more accurate computation of tractive effort used in physics.cpp

<table width=100%> <tr> <td> </table>

<!-- ----------------------------------  --------------- -->
<a name=consump></a>
<h4> Steam Consumption vs Supply </h4>

<blockquote>
...
</blockquote>

<!-- ------------------------------------------------------  --------------- -->
<hr>
<a name=brakes></a>
<h4> Brakes: Air and Independent </h4>

The independent brake pressure on the loco directly controls the brake, unlike the auto/air brake.   The brake force increases as the independent brake pressure increases.      suggest you try using the independent brakes with REL-Q(uick), REL-S(low), LAP, APP-S and APP-Q.  Last columns in output.

<p>
Auto/air brakes are like DCC in that the brake line both provides the impetus of the brakes, pressurizing the air reservoir in each car as well as signaling when to apply and release brakes.

<p>
<a href=https://www.wplives.org/forms_and_documents/Air_Brake_Principles.pdf>
<img src=Images/brakes.png align=right></a>

The locomotive has air pumps and tanks
to supply air to brake line connecting each car of the train.
Each car has a reservoir, triple valve and brake cylinders.
Air from the brake line supplies air to the reservoirs of each car.
Normal operation is to pressurize the brake line and reservoirs to 90 lb.

<p>
When the triple valve detects a drop in brake line pressure,
a difference in pressure between the reservoir and brake line,
it allows air from the reservoir to slow into the brake cylinder
which applies force the brakes contacting the wheels.
The triple valve stops the flow of air into the brake cylinder
when the reservoir pressure equals the brake line pressure.
The brake cylinder pressure is limited to 25(?) psi.

<p>
As soon as the triple detects an increase in brake line pressure,
it releases the air from the brake cylinders.
Air will flow from the brake line into the reservoirs
when the brake line pressure exceeds the reservoir pressure.

<p>
Various brake lever setting control the rate of air into or
released from the brake line.
Setting the brakes to LAP, maintains the brake line and brake line pressure.    
It takes time for a change in brake line pressure to propagate
down the length of a train.

<p>
A quick reduction in brake pressure will affect
the cars closest to the locomotive causing them to apply their brakes
long before cars at the end of the train see a change in pressure.
The various service settings, SVC1, SVC2
allow a gradual reduction in pressure and
braking to occur more evenly from every car in the train.

<p>
After the release of brakes,
air is needed to replenish the reservoirs
allowing additional brake applications
A single application of brakes
may drop the brake line pressure from 90 to 65 PSI.
A subsequent application after releasing the brakes
and without much time to replenish the reservoirs
may further reduce  reservoir pressure to 45 psi.
The number of brake applications is therefore limited.

<p>
<a href=Images/220702a_brks.png target="_blank">
<img src=Images/220702a_brks.png width=450 align=right></a>
The plot illustrates the brake line pressure (violet),
braking force (red) which is negative and
the air brake level setting (magenta)

<p>
The brake line pressure starts at zero but rapidly increases to 90 PSI.
The application of SVC1 causes a decrease in brake line pressure and
corresponding increase in braking force.
Moving the brake lever to LAP maintains both pressures.
Moving the lever to REL cause the braking force
to immediately drop to zero and allows the brake line pressure to increase.

<p>
The second brake application is EMER
which causes a rapid decrease in brake line pressure and
increase in braking force until is maxes out at a value of 10.

<p>
The third application of brakes sequences through SVC1, SVC2 and SVC3,
each increasing the rate of brake line pressure reduction and
the increase in braking force, also maxing out.
The brake line pressure was allowed to drop unnecessarily low.
Setting the brake lever to REL allows it to increase back to 90 PSI.

<p>
Braking a train requires anticipating the need for and amount of braking.



<h4> Stopping Time, Distance </h4>
<blockquote><pre>
    mph      %    sec     ft  fps/s
     25      1  113.9   2088   0.32
     25      2   56.9   1044   0.64
     25      3   38.0    696   0.97
     25      4   28.5    522   1.29
     25      5   22.8    418   1.61
     25      6   19.0    348   1.93
     25      7   16.3    298   2.25
     25      8   14.2    261   2.58
     25      9   12.7    232   2.90
     25     10   11.4    209   3.22

      5     10    2.3      8   3.22
     10     10    4.6     33   3.22
     15     10    6.8     75   3.22
     20     10    9.1    134   3.22
     25     10   11.4    209   3.22
     30     10   13.7    301   3.22
     35     10   15.9    409   3.22
     40     10   18.2    534   3.22
     45     10   20.5    676   3.22
     50     10   22.8    835   3.22
     55     10   25.1   1010   3.22
</blockquote><p/re>

<!-- ------------------------------------------------------  --------------- -->
<hr>
<a name=callFlow></a>
<h4>Steam Locomotive Physics (call flow)</h4>
<ul>
 <li>physics()
  <ul>
    <li> _reverser()
    <li> brakes()
    <li> engineTe()
    <li> update tonnage and total weight
    <li> account for grade
    <li> account for rolling resistance (when moving)
    <li> account for braking in loco and cars and brake direction
            not exceeding current force
    <li> update acceleration and speed
  </ul>
</ul>

<h4>Steam Engine Algorithm (call flow)</h4>
<ul>
 <li>engineTe()
  <ul>
    <li> update cylinder cycle parameters
    <li> account for slip on tractive effort (st.te)
    <li> resistanceLoco() - account for locomotive resistance
    <li> cylinderPressure()
     <ul>
        <li> track (while/integer) cycle 
        <li> determine partial cycle admission
        <li> determine change in cycle consumption
        <li> throttleDia()
        <li> srFlow() - update flow rate
        <li> interp() - steam chest pressure
        <li> mep()
     </ul>
    <li> cylForce() - compute tractive effort, wheel force on rails
    <li> resistanceLoco()
    <li> return st.lbFnet
  </ul>

 <li>engineRst()

 <li>engineInit()
  <ul>
    <li> engineRst()
  </ul>
</ul>

<h4>Brakes Algorithm (call flow)</h4>

TBD
