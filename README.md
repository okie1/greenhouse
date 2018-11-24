# Greenhouse Monitor
This is a device that keeps track of the temperature in my greenhouse and will help heat or cool depending on conditions.

![Greenhouse](https://github.com/okie1/greenhouse/blob/master/Overview.jpg)

## Overview
Every year my wife and I spend a small fortune on plants for the flower beds.  At the end of summer, we dig up the ones we want to save
the most and place them in plastic containers.  We keep the containers in our garage all winter long so the plants don't freeze.  The
bad thing about this is that all the plants take up a lot of garage space.  In addition to this, our garage has no windows, so the plants
suffer from not getting enough sunlight.   

This fall, we decided to try building a small greenhouse out back to keep the plants in.  The problem is, that we get weather where the
temperature can dip below freezing for prolonged periods of time.  I knew that there would be times where the temperature in the
greenhouse would dip below freezing as well.  So, I needed something to help generate some heat during those cold spells.

This project is a temperature sensor and a few relays that turn on/off based on the temperature.  One relay turns on heat lamps that
provide heat when it is cold.  The other relay activates a fan that will help cool the greenhouse should the temperature get too warm.

## Parts
* 1 - Particle Photon
* 1 - 5V power supply, 2.5amp
* 1 - breadboard
* 1 - TMP36 temperature sensor
* 2 - 3.3v relay modules
* 1 - 10nF capacitor
* 1 - power outlet
* 1 - project box
* Misc hookup wire

## Circuit
![Circuit](https://github.com/okie1/greenhouse/blob/master/circuit.jpg)

## Code
The code is posted on this GitHub feed: [https://github.com/okie1/greenhouse](https://github.com/okie1/greenhouse)

## Assembly
Most of the details are detailed in the circuit diagram.  The build started from a diagram and code example from the particle websight.  One item to note is a modification I made to the electric outlet.  On the hot side of the outlet I broke off the tab such that I could use the top and bottom plugins on separate circuits.

## Results
As you can see from the photo, I did not take any pains with the wiring.  I did this with the intention of it being a temporary build.  However, it works so well, I may just keep it around for a while.  It will be interesting to see how durable a build that uses a breadboad will be....even though it just basically lays on a stool and runs.  

It is easy to check in with the Particle app from my phone to monitor the current conditions in my greenhouse.  Here is what that looks like:
![ParticleApp](https://github.com/okie1/greenhouse/blob/master/ParticleApp.jpg)
From my phone I can change the temperature thresholds for each relay.  The values are saved in EPROM so they are available even after a reboot of the device.  I can also see how long the device has been running and if it still is.  I added a remote reboot command to it as well by sending the text "reboot" to the App_MiscCmd function.

## Hindsight
It's a brand new build..... I'll check in later.
