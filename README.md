# Open Source Worm Gear winch
A public repository to share the stls and Fusion 360 files for a worm gear winch

## My Intent
I am sharing this handy winch because it works well for me and my use case. Hopefully, it works well for someone else. I have been learning Fusion 360 off and on for the last year for smaller projects.

I tried my best to make everything easy to 3d print. I have not noticed an issue with the worm and the plastic shearing on the layer lines. 
I do use heat-set inserts in some locations, which. In most locations, you can use a nut instead.

## Current State

It is powered by a 775 brushed motor and controlled by an Arduino with a motor module that is way overkill because it only draws 1 amp at max load. The remote is another Arduino with an OLED screen powered by a single li-ion battery and type c for changing! The remote can cycle has a cycle function to communicate to multiple winches. 

## What is coming next for this project!
I want to simplify the electronics. I used MOSFETs to control a motor controller. However, I want to switch to a `BTS7960` module or something similar.

It would be neat to shrink the transmitter and offer a single winch version. Currently, the remote can cycle through multiple winches by changing the address.

The spool is not designed the best and needs to be modified to ensure the string cannot jump over and into the side of the winch and is relatively small. 
Its string capacity is about 12 ft. 

I need to design a second winch that does not require the additional off-set pulley.

It would be awesome to add a pulley system to increase pulling power.

## Capacity

I use a micro paracord rope with 100 lbs tests, and I have been able to lift 100 lbs with this winch in its current condition. The winch is comprised of two main parts.

There is the winch which contains the worm gear, and the electric motor that drives the spool. I am using a Worm Gear because it takes zero power to hold stuff in the air and is a relatively small package for the gear ratio.

The second part is the load-bearing pulley. It is designed to handle the forces better when mounted to the ceiling and helps smooth the lifting action.

## What is include

I am sharing the current stls and Fusion 360 files for the winch and transmitter.
I also created a transmitter and receiver for the winch because I wanted a wireless remote to control the winch. 

I will try my best to demonstrate the wiring of the transmitter and receiver and its accompanying Arduino code. It uses 
rf240l+ trans-receviers to communicate with eachother.

I have these winches in my garage to hoist RC planes to the ceiling, and it saves space, and I am too lazy to use a ladder whenever I want to retrieve my planes.

## Assembly

After assembling, you should run it with greased gears to help break everything in for a couple of hours. 

### Printing recommendation:

I believe the smallest print bed you can get away with is 220mm x 220mm

All parts are in the recommended orientation.

5 perimeters
4 top and bottom
31% infill
.2 layer height

Special Printing Instruction for the Worm
5 perimeters
4 top and bottom
31% infill
.12 or .08 layer height

The smaller layer heights help make the power transfer from the worm to the gears much smoother. 
You can get away with a `.2` layer height but not recommended.

NO SUPPORTS NEEDED

Expected Printing time: 
Slow Printers: ~ 48 hrs

Faster Printers: ~ 22 hrs

I am guessing the speed for a slower on an Ender 3. 
I have a Voron V2.4, and it takes about 22 hrs for me to print everything out. 

#### Hardware
Currently, to assemble the winch, you will need the following non-printed parts:

M3 socket head screws:
    60mm * 4-8 for the case
    25mm * 4 for the gear. They act as pins to help reduce the chances of 			searing the plastic layers
    30mm or 35mm for the pin to connect the gear to the rod
    15mm for the spool pin to connect it to the rod
    50mm * 4 for the spools screws. Help it from splitting
    30mm * 4 for the worm mounting bracket

8mm threaded or grounded rod
    could use carbon fiber rods; however, the load capacity is very small but easy to work with

    114MM for the rob that connects the gear and spool
    100-110mm for the rob that connects the worm to the motor
    
    To mark the drill locations for the rod, you will need to assemble it and mark it partially.

8mm to 5mm couplers
https://www.amazon.com/gp/product/B07RMZCLZ3/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1


All rotation uses bearings for long service life and increases load capacity
608zz bearings (skateboard)
    Cheap and good: https://www.amazon.com/FaGoBearing-Premium-Inline-Bearings-Roller/dp/B07V3NG2XR/ref=sr_1_4_sspa?keywords=skateboard+bearings&qid=1658343544&sr=8-4-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyQzdKSUZaRTQ4NlpVJmVuY3J5cHRlZElkPUEwMjYyODEzMTgzM0FMNjFNMVpNUSZlbmNyeXB0ZWRBZElkPUEwMDc3NDUwMkRVSERNUDJQUFZMRCZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=

8mm Thrust bearings
    I am using thrust bearings because the prototype would melt together in certain locations. These eliminate that from happening
    https://www.amazon.com/uxcell-Bearings-Diameter-Thickness-Hardness/dp/B07PDXYQTJ/ref=sr_1_14?keywords=8mm+thrust+bearing&qid=1658343648&sprefix=8mm+thrust+%2Caps%2C106&sr=8-14

Electronics
 775 electric motor
 https://www.amazon.com/775-Motor-12V-6000-12000-Electronic/dp/B08662QSZL/ref=sr_1_1_sspa?crid=3NJKRRKDI3DL1&keywords=775+dc+motor&qid=1658354595&s=hi&sprefix=775+dc+moto%2Ctools%2C91&sr=1-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyRTFDMDc3M0hYUFU5JmVuY3J5cHRlZElkPUEwMTQwMjg3M05CTlZQSEtZWEk0WiZlbmNyeXB0ZWRBZElkPUEwMjU0ODAzM0RPMlRDWTBZR0JaWCZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=

Arduino Nano: 
https://www.amazon.com/Arduino-Nano-Every-Single-Board/dp/B07VX7MX27/ref=sr_1_3?keywords=arduino+nano&qid=1658354680&sr=8-3

Seeed Xiao RP2040
https://www.amazon.com/Microcontroller-Dual-Core-MicroPython-CircuitPython-Interfaces/dp/B09NNVNW7M/ref=sr_1_2_sspa?keywords=seeeduino+xiao&qid=1658354708&sprefix=seeed%2Caps%2C110&sr=8-2-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzSlM3VkdUWjdIWTZFJmVuY3J5cHRlZElkPUEwMDc4MDMyMTlMNjFCMUFLNkU1SiZlbmNyeXB0ZWRBZElkPUEwNDI3MDEyM0lOQk1FQlREVkg3RCZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=

Mosfet Module
https://www.amazon.com/Anmbest-High-Power-Adjustment-Electronic-Brightness/dp/B07NWD8W26/ref=sr_1_4?keywords=arduino+mosfet+module&qid=1658354745&sprefix=arduino+mos%2Caps%2C116&sr=8-4


Voltage Step Down Regulator
https://www.amazon.com/MP1584EN-DC-DC-Converter-Adjustable-Module/dp/B01MQGMOKI/ref=sr_1_3?crid=20FNT6DXGGMR5&keywords=5v+step+down&qid=1658355023&s=electronics&sprefix=5v+step+down%2Celectronics%2C97&sr=1-3

24 voltage power supply
https://www.amazon.com/dp/B07PWZQ4MB/ref=emc_b_5_i

Motor Driver
https://www.amazon.com/gp/product/B075L7YDR9/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1

NRF24L0l
https://www.amazon.com/gp/product/B0829ZQ97G/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1

### Transmitter Electronics 
Oled Screen
https://www.amazon.com/gp/product/B00O2LKEW2/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1

Arduino Nano: 
https://www.amazon.com/Arduino-Nano-Every-Single-Board/dp/B07VX7MX27/ref=sr_1_3?keywords=arduino+nano&qid=1658354680&sr=8-3

Seeed Xiao RP2040
https://www.amazon.com/Microcontroller-Dual-Core-MicroPython-CircuitPython-Interfaces/dp/B09NNVNW7M/ref=sr_1_2_sspa?keywords=seeeduino+xiao&qid=1658354708&sprefix=seeed%2Caps%2C110&sr=8-2-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzSlM3VkdUWjdIWTZFJmVuY3J5cHRlZElkPUEwMDc4MDMyMTlMNjFCMUFLNkU1SiZlbmNyeXB0ZWRBZElkPUEwNDI3MDEyM0lOQk1FQlREVkg3RCZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=

Momentary Switch
https://www.amazon.com/gp/product/B07QH9WV12/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1

5v Step Up Voltage Regulator
https://www.amazon.com/gp/product/B094XJL149/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1

1S Li-ion BMS
https://www.amazon.com/gp/product/B07PKND8KG/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1