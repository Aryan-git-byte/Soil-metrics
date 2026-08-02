# SoilMetrics

SoilMetrics is an open-source, low-cost IoT-based soil health monitoring system designed for small and local farmers. It measures key soil parameters like moisture, temperature, NPK, EC, and Temperature in real time.

# 2026-07-05: AHHHHHHHHHHHHHHH!!! Project completed!!!!

**Total time spent: 2 hour 8 min**

it was all about arranging repo, and writing README.md:
i started by arranging the repo, removing unused files from git, files, repos etc. then i exported bom, added LICENSE, started writing README.md, learnt few md tricks between that. 
My line got cut in between, and it rained so went outside for almost half an hr ig.
then came, exported scheamtics images, put them into readme, took pcb ss, added it. and then wrote assembly instruction, firmware instruction, allat. blah blah.
then ended the repo and commited it.
![image.png](https://cdn.hackclub.com/019f3254-ff0c-73cc-bf7b-e6fe2d042d4f/image.png)

# 2026-07-05: making bom

**Total time spent: 3 hour 20 min**

okay, so the plan was to put link and price in each symbol, and later export BOM.
i started by searching the main components and put their links , for some i had to change footrpints depending on whats available such as sd card, sim card, inductors, some elctrolytic caps etc.
it was like this![image.png](https://cdn.hackclub.com/019f314d-5e2c-78e5-a48c-366dd056d866/image.png)

after doing all these, i resolved the DRCs, which i just had to change a hole from tht to NPHT, it was caused by migrating from easyeda to kicad this one:.
![image.png](https://cdn.hackclub.com/019f314e-8c39-7773-bec6-e7d01fa3f6e5/image.png)

after this i quoted my pcb at lioncircuits whic was for 
![image.png](https://cdn.hackclub.com/019f314e-ef27-7227-9b97-1a3c17d1e336/image.png)
40-ish us dollar.

# 2026-06-28: lets make ZINEE!!! 

**Total time spent: 1 hour 41 min**

for rendering i changed the logo colors to white so they r visible:
![image.png](https://cdn.hackclub.com/019f0d5f-c3d9-78c2-9412-cf4b6ef18b10/image.png)
![image.png](https://cdn.hackclub.com/019f0d5f-f727-7ef6-8563-a1e1c623bfff/image.png)
and rendered it:
![image.png](https://cdn.hackclub.com/019f0d61-bffd-7843-97bf-995fe6ba239e/image.png)

after that i started designing the zine poster
which turned out to be the favourite part of mine in whole project:
![image.png](https://cdn.hackclub.com/019f0d64-a73c-70f2-ae2c-932ecfea9ce7/image.png)

# 2026-06-28: CADing time!!!!! (again)

**Total time spent: 1 hour 44 min**

![image.png](https://cdn.hackclub.com/019f0d5a-e40d-73a2-a882-b54c89b90c7f/image.png)
i started by cutting this area:
![image.png](https://cdn.hackclub.com/019f0d5b-1039-7855-815a-68152e9982d2/image.png)
and exported normal tft 3d model and started designing around it
here is the front design:
![image.png](https://cdn.hackclub.com/019f0d5c-5cee-7c14-8621-5cf921f23726/image.png)
then on the back i started sketching for pegs for screws:
![image.png](https://cdn.hackclub.com/019f0d5c-e125-7f71-a8c6-e77e9be1f2b6/image.png)
and added back cover, then i searched how to add finger rest in fusion and followed it to make ts:
![image.png](https://cdn.hackclub.com/019f0d5d-c8ea-7ed0-b13a-2a923e8ed0bd/image.png)
then i put the logo:
![image.png](https://cdn.hackclub.com/019f0d5e-1f09-765a-b911-c1bb08a545f7/image.png)
and tried to render:
![image.png](https://cdn.hackclub.com/019f0d5e-83fb-7cab-8ce2-f3378fc1a867/image.png)

# 2026-06-28: CADing TIME!!!!

**Total time spent: 1 hour 9 min**

i started making the walls of each side around the pcb
and wtf is this bruh:
![image.png](https://cdn.hackclub.com/019f0d56-2a37-7e4a-aa80-3f27025067df/image.png)
so i decided to restart the CAD, and made another file and imported pcb and started working on it.
then i downloaded the sensor model and imported it:
![image.png](https://cdn.hackclub.com/019f0d57-51a3-7576-867d-59fb815dec17/image.png)
![image.png](https://cdn.hackclub.com/019f0d57-6b53-7472-be4b-8b867cb722f7/image.png)
then i tried like too much to find the 3d model of my display but sadly i couldnt find it, so i paused my work and mailed the manufacturer asking for the display but they didnt had the model so my plan now will be to design the case around the normal rpi 3.5" dispaly and submit for design review and when i get the display i take it and create the 3d model,double check my pcb etc then move forward

lapse link - https://lapse.hackclub.com/timelapse/SgSomI8laiaZ

# 2026-06-19: Rendering and CADing

**Total time spent: 1 hour 36 min**

i started by resolving those 67 drc errors due to curve then i imported the model in blender then my pc cryed then i finally got some good renders hehe:
![image.png](https://cdn.hackclub.com/019edf50-d446-70a9-9da4-050ac0b62acd/image.png)
![image.png](https://cdn.hackclub.com/019edf50-e6cd-7d80-8375-becf3992686e/image.png)
 and yeah the model differ in the down one because first time imported wrong pcb, and also this took me alot of problem cuz idk a shit abt blender so uyhh..
after that i started working on the 3d model of pcb. obv its enclosure
![image.png](https://cdn.hackclub.com/019edf51-43d4-7244-bbed-1d81520d8dc0/image.png)

then i added moutning holes to the pcb

# 2026-06-19: tidying the schematic and curving the tracks

**Total time spent: 1 hour 33 min**

today i started by tidying up the schematic so its more readable, and clear for reviewer to review and so it is more polished:
![image.png](https://cdn.hackclub.com/019edf4f-5779-71ed-aa55-de0f0ab94137/image.png)
![image.png](https://cdn.hackclub.com/019edf4f-74a3-72e9-a4de-9399fa736d9c/image.png) 
 after that i fixed leftover DRC and started confirming the footprints for the last time and then i put my logo onto the backside of the soilmetrics and i also curved my traces:
![image.png](https://cdn.hackclub.com/019edf4f-cf5a-73d7-9d94-ba32acb966f7/image.png)
![image.png](https://cdn.hackclub.com/019edf4f-e22c-7e16-a090-4c32b9c11143/image.png)

and after curving traces i got hit by another 67 DRC errors. so again i started fixing them.
and tbh these curve tracks looks so cool.

# 2026-06-19: Fixing some issues and fencing

**Total time spent: 59 min**

a guy suggested me to add leds in the sim module for debugging help and so i added leds, in the schematic :
![image.png](https://cdn.hackclub.com/019edf4d-b87e-702c-9ae0-05a11e41ed42/image.png)
then i added via fencingt the rf trace and fixed missing connections errors a nd fixed DRC errors.
then i started cleaning the silkscreen and designed it 
![image.png](https://cdn.hackclub.com/019edf4d-eaff-7e9a-bc50-3988be5bcda0/image.png)
![image.png](https://cdn.hackclub.com/019edf4e-0b96-7b65-952d-2077b9b67420/image.png)

# 2026-06-19: updating kicad version

**Total time spent: 48 mins**

today i migrated kicad 9to kicad 10 . and again started resolving the DRCs, and also noticed that my display header was orientated in wrong way. so i fixed that and removed its routing and started rerouting it and completed it:
![image.png](https://cdn.hackclub.com/019edf4c-ce53-72fd-bb43-d0064b90a8f2/image.png)
 after that i ran a script to put stitching via but that wasnt good .so i removed it and decided not to use it

# 2026-06-19: Rearranging the layout

**Total time spent: 2 hour 31 min**

i Started by rearranging the components and routing em one by one, starting with the crucial traces that had RF carrying around. i layed out the sim slot, sd card holder, battery holders, and the headers and the screw terminals.
![image.png](https://cdn.hackclub.com/019edf4a-6151-7e54-abcf-f9c4494e1a94/image.png)
 then i started routing the ratnets including those of MCUs, headers etc:
![image.png](https://cdn.hackclub.com/019edf4a-8d1e-7dd2-8cb2-ef52b3fa1e2e/image.png)

then i curved the pcb edges and started routing other components then i completed routing then placed copper fill and stitching vias. and remove via from keepout zones

after that i started resolving the DRC errors and almost completed it then one guy suggested to have a 4layer board so that RF can work peacefully, so i did that and added another 2 layers. and fixed the RF routing thickness.

# 2026-06-19: Designing the PCB layout

**Total time spent: 4 hour**

i first started by importing and asiigning footprints to each symbol.
then i fixed the errors occuring when i converted the schema to pcb, which were mostly pin assignments error.
then i started layout the board and components. and defined the pcb border, man this took so long like it just smtimes didnt worked idk why.
so like after doing all ts, my board looked smthg like this:
![image.png](https://cdn.hackclub.com/019edf46-818b-7b4b-8b4a-ba08f2441fbb/image.png)
then i wasted so much time routing it, this way -that way etc. and it just didnt satisfied me. i had to use vias etc and it didnt looked professional and good.
so after that i started assigning 3d models to those which didnt had it and unrouted everything made the board more compact and started routing it keeping aesthetics and professionalism in mind
You can see my messy process in the lapse below, and i forgot to screenshot it while i was working, sry for that.

### Recording Links

- https://public.lapse-hackclub.link/timelapses/XOk-CF6XGFQ6/timelapse-XOk-CF6XGFQ6.mp4
- https://public.lapse-hackclub.link/timelapses/igRPsVUnFXjy/timelapse-igRPsVUnFXjy.mp4
- https://public.lapse-hackclub.link/timelapses/4eXL_hUHumv1/timelapse-4eXL_hUHumv1.mp4

# 2026-06-19: Designing the Schematic

**Total time spent: 1 hr 46 min**


this time i started by copying the BMS from other project of my mine , lol:
![image.png](https://cdn.hackclub.com/019edf42-3466-7211-a55b-db5831bfd61b/image.png)
and then i completed the charging circuit too
![image.png](https://cdn.hackclub.com/019edf42-5b39-7eda-b30d-86f800d056c2/image.png)
after that i copied another 3.8v buck onto my schematic. since dropping 8.4 volts to 3.8v using LDO would be tuff, i decided to use one buck circuit , to step down it to 3.8 so i can then put LDO and step it down to 3v3. and step down 8.4v directly to 5v using LDO.
![image.png](https://cdn.hackclub.com/019edf42-8f1c-7a59-9ebb-3737a996c1c2/image.png)
![image.png](https://cdn.hackclub.com/019edf42-c1a5-7e38-b827-eea7784fd908/image.png)
i started working on the main mcu sheet, and added a hierarchial sheet then added the esp32 and its peripherals and the boot and reset buttons:
![image.png](https://cdn.hackclub.com/019edf42-fc8a-7feb-b31b-69c5b730f9e0/image.png)
then i added sim7080g and its peripherals:
![image.png](https://cdn.hackclub.com/019edf43-9e6d-7922-95e8-17576ec5fa62/image.png)
a logic level converter :
![image.png](https://cdn.hackclub.com/019edf43-ed78-7b5f-b876-b5488e60c388/image.png)
![image.png](https://cdn.hackclub.com/019edf44-0f49-7868-acfa-49ef7926d2cb/image.png)
then the main display headers.
after that i connected the nets to the esp32 .
![image.png](https://cdn.hackclub.com/019edf44-520a-7bc3-9e38-591e94c918c6/image.png)
then the max3485 and the sd card:
![image.png](https://cdn.hackclub.com/019edf44-7c11-720e-a58b-02aa117753da/image.png)
and completed the schematic almost

### Recording Links

- https://public.lapse-hackclub.link/timelapses/-C07Upd8Ah_I/timelapse--C07Upd8Ah_I.mp4

# 2026-06-19: Comeback

**Total time spent: 34 min**

hi, so i m back in soilmetrics after few days, so basically i started outlining the needs of the board in the starting which were as follows:
- a display on which the farmer can see all the results
- LTE + GPS feature. LTE for IoT and GPS so that the device can fetch the location, then send it to a server, and then teh server can respond with weather data of that place, and i have plans for the V3.1 to have cloud AI on the device.
- a RS485 receiver for the sensor to be interfaced with
- A reliable BMS in such a way that it doesnt explode and can give 12 hr uptime smthg
- sd card to log the readings

after that i had two options , 
1. either i use this WT32-SC01 Plus (https://probots.co.in/esp32-s3-wireless-tag-sc01-plus-development-board-with-3-5-inch-lcd-ips-display-touch-screen-wifi-ble.html) which has integrated RS485 interface, SD card interface, and a display.So my idea with this is that i design one more carrier board that sits perfectly on this one and fulfilll other features that this one dont have such as BMS and the LTE+GPS.                           OR
i redesign it fully from scratch, i mean this will work too. but the concern is that it may not be integrated as this one or maybe other problems etc + i prolly think that way 1 will be cheaper .

so after asking cool peoples about this, 
![image.png](https://cdn.hackclub.com/019edf3f-0c73-790c-a670-405f27c8193a/image.png)
i decided to redesign it and started working on it.
I started by finding the symbols, and then started laying out the schematics and modules :
![image.png](https://cdn.hackclub.com/019edf3f-5555-72cc-8b77-1da3827005b4/image.png)
then for the 2S BMS, i started by first creating the symbols for the TP5100 cuz i m lazy to import it lol.
and then started wiring it out . also updating the symbol accordingly so that it could look clean 
![image.png](https://cdn.hackclub.com/019edf3f-b038-7e82-9b57-e18b0d7516b2/image.png)
after that i copied the HY2120 from my other project.

### Recording Links

- https://public.lapse-hackclub.link/timelapses/0y9sGz3QpZsh/timelapse-0y9sGz3QpZsh.mp4

# 2026-06-19: 4/3/2026 - Hi.....

**Total time spent: 9.0h_**

_Time spent: 9.0h_  

i know i m 1 month late, and yup i did worked in between too. and somethings didnt go the way i wanted em to.
starting off after this was successfully working and i was head over heels with this achievement not because it showed readings or good UI but i was happy because first of all i have been working on ts from days, day and night. so after this i was feeling very confident and then i started cutting the sunfoam board for the enclosure(yhh i thought to make a enclosure from the sunfoam before 3d printing it to just double check my dimensions, tolerances etc.
and i soldered all the components:
![image](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTMzNDgzLCJwdXIiOiJibG9iX2lkIn19--c2b751402b2ded613bc4d83b5386ceb85644fcf2/image.png)
to do all this i was awake a literal night, like i didnt even slept that night. so it went like first i cut out the sunfoam(this alone took 3 trials, cuz sunfoam board breaks easily).and did soldering of the power section, because ik once that will be reliable rest will be a piece of cake, between that i blew up my mini 360 buck converter, so i replaced it with the og lm2596,after which i slept at about 6 am smthg. and then woke at 8-9 and started soldering rest of it. after soldering it. i tested it like the display, it didnt worked. last i knew was that i blew up my buck converter due to which the tft blew up too.idk what happened, how it happened. the last time i tested it was this time:
![image](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTMzNDg0LCJwdXIiOiJibG9iX2lkIn19--6af4cb09cb8e5f6627b98c7ca8d1d71b2dbc43e6/image.png)
![image](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTMzNDg4LCJwdXIiOiJibG9iX2lkIn19--94c247b58f8ef3e65c7b2a1308de6e5bce5050fb/image.png)
and let me remind you i was doing all this from my savings, which eventually came to an end.and till now i have spent more than 10k inr on this as of now(approx 107 usd) and with this failure my savings too came to an end. after that i thought that the tft is gone but not the other parts, so i desoldered all, stripped it down to bare minimum and then tried , and guess what? yup it failed too. i was already very demotivated and drained as of now . so i left it , and packed everything in a box and left it in a cupboard until on march 21, i came back with a new max485 module, tried this time first with the arduino uno because both max485 and arduino were 5v logic , and arduino uno had software serial so it was easy to implement and yup it did worked, then i tried with that atsamd21 based devboard, and god dang ittt, this max485 module blew too,and it almost took the devboard on the verge of blowing up too. but it got saved somehow.
i do have timelapse of this day, because last time i was working i didnt knew of lapse etc so i couldnt record myself crying and ragebaiting , u can watch it here: https://lapse.hackclub.com/timelapse/8rE2vU6fCmCs
it is around of 3 hr.


so yeah this was all the previous ragebait + breakdown moments, now i m thinking to start it again but with appropriate modules and not doing bruteforce or smthg like i did till yet.

onto proper v3, bbut this time with a proper plan and a pcb

# 2026-06-19: 2/27/2026 - some updates

**Total time spent: 1.0h_**

_Time spent: 1.0h_  

![17722037394741000893386619170592](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTEyMjgxLCJwdXIiOiJibG9iX2lkIn19--e1a112716e297f583fd33c668482dd71dc1ecadf/17722037394741000893386619170592.jpg)![17722037515627499167181652850331](https://raw.githubusercontent.com/aryan-git-byte/soil-metrics/main//user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTEyMjgyLCJwdXIiOiJibG9iX2lkIn19--813eb41e04865c2bf5469803c43d81f6b87f8c9e/17722037515627499167181652850331.jpg)![17722037624975476929164747784854](https://raw.githubusercontent.com/aryan-git-byte/soil-metrics/main//user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTEyMjgzLCJwdXIiOiJibG9iX2lkIn19--a0ab3c96bb5052729238d803a3c9d3003813dada/17722037624975476929164747784854.jpg)


Added some features in the CAD to support antenna,charging module etc and umm like aaranged it neatly on cardboard to test the sensor:
![17722038499937718798686286489273](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTEyMjg3LCJwdXIiOiJibG9iX2lkIn19--d560a678eeac684309423b32b0f89d3a8d42b589/17722038499937718798686286489273.jpg)
Next i will make a enclosure for the device with sunboard:
![1772203965260202302550315049232](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTEyMjkxLCJwdXIiOiJibG9iX2lkIn19--ef508368dd0a34d066c0ed7f84699fb76c38bc53/1772203965260202302550315049232.jpg)

# 2026-06-19: 2/26/2026 9 PM - UI

**Total time spent: 0.2h_**

_Time spent: 0.2h_  

![17721210372289165371290562398791](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTExNjkyLCJwdXIiOiJibG9iX2lkIn19--d524890bc03c9dd9daaa74d88c6f1fb238fcd035/17721210372289165371290562398791.jpg)

So I did the changes and made it show all the parameters on the display in a good format and this is all bare metal code and the code uses only 2 libs which are arduino.h and wiring_private.h

# 2026-06-19: 2/26/2026 8 PM - working finally

**Total time spent: 1.8h_**

_Time spent: 1.8h_  

![1772118717938479645331332089647](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTExNjc4LCJwdXIiOiJibG9iX2lkIn19--76d48f5fe5707b1e7db80db4e93d5e9465648d43/1772118717938479645331332089647.jpg)
![17721187344088848580099755748484](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTExNjc5LCJwdXIiOiJibG9iX2lkIn19--75733fb3962e5f14e3455d59806d3d8d1fcc3b60/17721187344088848580099755748484.jpg)
We finally got the readings from the DevBoard yooooo, yahyyyyyy
Now i'll update you guys with the code & schematic too ASAP, lessss goooooooooooo

........

# 2026-06-19: 2/26/2026 7 PM - Done, bought the max485

**Total time spent: 1.5h_**

_Time spent: 1.5h_  

![17721126883098113475692449284550](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTExNjQzLCJwdXIiOiJibG9iX2lkIn19--54b18815582e1529a70da5fe2ab26adf8e31fe43/17721126883098113475692449284550.jpg)
![17721127110081257172053298803849](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTExNjQ0LCJwdXIiOiJibG9iX2lkIn19--50fe63285030722b14b794c9ffa94c30b03e3691/17721127110081257172053298803849.jpg)

Done , it is working data is coming now , max485 was the problem Obv 
And I also tested the dev board with TFT and wrote custom sercom code to display  it:
![17721129033243615115620726582636](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTExNjQ2LCJwdXIiOiJibG9iX2lkIn19--0ed574645c2de0877225442d21236af2eed45cd3/17721129033243615115620726582636.jpg)

# 2026-06-19: 2/25/2026 - Major Problem

**Total time spent: 4.5h_**

_Time spent: 4.5h_  

What happened is that I first soldered the max485 through level shifter to the dev board and between that things that happened were :
- the VCC pad got out 
- the RE pad too
so what i thought was tk directly solder these from the ics and dje to which I by mistakenly touched the live 5v wire to gnd which also tripped my devboard and other buck,boosts etc but I thought that max485 should work even after that so I did like used it but it's issue was that I tried like more than 12 codes and it didn't read the sensor values so then and btw it was already night by this had gone for some breaks & dinner in between so I soldered the whole thing kept it on the table then went to dinner then came read datasheets, took help from AI in coding & troubleshooting then i figured out that the sercom is not available on the pin I am using so I desoldered it and put on another pinset , tried again but still didn't worked so at last after losing all the hopes , I thought to try this with an Arduino uno since i'd already used this sensor one time with uno and I have a perfect code which worked last time in its previous iteration so like i desoldered everything & soldered em to Arduino uno then tried the code in it and it still didn't worked so I got to conclusion that the max485 is faulty, and i thought this could be due to the short I did in that board so what I did was that I had another board of which ic got burned but everything else was fine so I desoldered the ic from the board I was using previously to that donor board (body ig) this alone took hell lotta stuff like i didn't had a hotplate so that was also a reason for this late and i flattened out a scrap soldering iron which was thrown in my institute's backdrawer , so i took it and flattened it it loooks like this btw :
![17720191633152056917411161782742](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTExMDcwLCJwdXIiOiJibG9iX2lkIn19--a6d288c58daaa6dd1c87ce2599bbbcf8f8e2ea6a/17720191633152056917411161782742.jpg)
It's power plug was also cut so fixed it too then after that I soldered out the ic from the main board:
![17720193228083469726520481188980](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTExMDcxLCJwdXIiOiJibG9iX2lkIn19--110000aa7358f7eb2e3224dcb65babe273cdb04e/17720193228083469726520481188980.jpg)
And soldered it on another one :
![17720194110202603768889923781507](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTExMDcyLCJwdXIiOiJibG9iX2lkIn19--c6206063f021da3550fd6201a758c25a9c9ec8b9/17720194110202603768889923781507.jpg)


And yhh it didn't worked TT

and also local shops didn't had this max485 so gotta ask it smwhere else or maybe try any other alternative 

The current setup which doesn't work is :
![17720195519435045405732496398572](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTExMDczLCJwdXIiOiJibG9iX2lkIn19--63d6299b004de1ee549c550241f319a253e8bacc/17720195519435045405732496398572.jpg)

# 2026-06-19: 2/24/2026 - Finally working

**Total time spent: 1.0h_**

_Time spent: 1.0h_  

![17719347658643116043165573525715](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTEwNDAxLCJwdXIiOiJibG9iX2lkIn19--b229f45e0191f5e00b8127e8a12fccbf44e1a5ac/17719347658643116043165573525715.jpg)
Soldered the battery directly to the tp4056 and then put the 5v boost after after the battery and buck after boost
And then connected 3v3 to the DevBoard next is level shifter and max485
Also I identified the problem yesterday which was the BMS as it tripped whenever boost or buck borrowed power from it

# 2026-06-19: 2/23/2026 - Materials collected

**Total time spent: 1.0h_**

_Time spent: 1.0h_  

Bought all the rest components and soldered the BMS also some changes in plan
I couldn't find 2s bms so am using 1s and 1 buck and 1 boost 
Here's the battery soldered with switch , bms, and buck

![17718436341475709654256739045312](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTA5ODE4LCJwdXIiOiJibG9iX2lkIn19--ee152afceaa6586c3c1a27810744573e538797f8/17718436341475709654256739045312.jpg)


Waittttt i just realised that I soldered the positive and negative that leads to buck on the cell instead of BMS 😭
Lemme fix it real quick
Okay so I encountered a problem that when I connected the buck to the p+ and p- of the BMS , it doesn't give current in our
And the resistance between our + and out- in the buck is. Approx 8.3 k ohms and when I switch on the power switch ,in continuity mode it beeps
Also when I connect directly to the battery,skipping the BMS it works but not on p+ and p- 
Will have to troubleshoot it

# 2026-06-19: this is my case on which i started working, in this the tft and the module and all the other modules will go, and the sensor will be out in a joint

![image](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTA5MDE2LCJwdXIiOiJibG9iX2lkIn19--40bb24538d6a7d82b6083d824adaf46bd7491bfe/image.png)

i have checked all the dimension used as of now with caliper and double checkd it

# 2026-06-19: 2/22/2026 4 PM - started working on the case

**Total time spent: 2.8h_**

_Time spent: 2.8h_  

![image](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTA5MDE0LCJwdXIiOiJibG9iX2lkIn19--afbd73614bc6609270a39f2dfd3efdd65c9ad204/image.png)

# 2026-06-19: 2/22/2026 12 PM - Made the Schematic

**Total time spent: 2.0h_**

_Time spent: 2.0h_  

So i want to make an affordable device for farmers which can tell them about their soil's health and show parameters such as NPK, EC, pH, Moisture and Temp. 
It will be based on custom devboard by the smartelex which consits of gps, gsm and a powerfull processor i.e ATSAMD21
![image](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTA4OTM0LCJwdXIiOiJibG9iX2lkIn19--94ce9bbed9c887643be19b50513a23e9c73ea1ff/image.png)


on top of that for the UI we will use a resistive touch 2.8" TFT display:
![image](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTA4OTM1LCJwdXIiOiJibG9iX2lkIn19--9c3d101bd2b795fce5361032c01d82e4477e29e2/image.png)

For the Sensor we'll use the :
![image](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTA4OTM2LCJwdXIiOiJibG9iX2lkIn19--b5586fffb5a1aa30ddbbaa149306856819039a49/image.png)

And to interface the sensor i will use a max485 module along with a level shifter because i already have a max485 module and the atsamd operates on 3v3:
![image](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTA4OTQyLCJwdXIiOiJibG9iX2lkIn19--8c06c371ea9f5bf50801eb4a77ac3a170a522ab7/image.png)

and aside of these for protection , charging and voltage regulations we'll use:
1x 2s BMS
1x 2S battery holder
2x MP1584 &
1x Barrel jack

and the connection of all the modules will be done according to this schematic:
![Schematic_Soil-iteration-v3_2026-02-22](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTA4OTYwLCJwdXIiOiJibG9iX2lkIn19--8d00ee70320b846d6be26d6a411de9e247225926/Schematic_Soil-iteration-v3_2026-02-22.png)

and for powering the i'll use 2 5000 mah cells:
![WhatsApp Image 2026-02-22 at 12.46.55](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTA4OTYyLCJwdXIiOiJibG9iX2lkIn19--f1c1edb5020602bd3c3fb02b4eb8f3db6e45d8a6/WhatsApp%20Image%202026-02-22%20at%2012.46.55.jpeg)

and currently i have all the materials too except the level shifter, 2s bms, and mp1584 which i will buy mostly in 1 or 2 days too:
![WhatsApp Image 2026-02-22 at 12.49.53](https://blueprint.hackclub.com/user-attachments/blobs/proxy/eyJfcmFpbHMiOnsiZGF0YSI6MTA4OTYzLCJwdXIiOiJibG9iX2lkIn19--92c8395c0a9def09f76f41dc2a65c6178e226cfe/WhatsApp%20Image%202026-02-22%20at%2012.49.53.jpeg)

so next i'll prepare the case for this and will also solder and try components after that
