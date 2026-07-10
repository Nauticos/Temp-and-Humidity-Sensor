# A temperature and humidity sensor Build Journal

## Jul 8, 2026, 7:33 PM

Today I started to design my breadboard project. I will be making a temperature and humidity sensor for my room, since I want to know how hot/humid my room is. I chose the ESP32 kit so I have the option to expand using Wifi in the future (e.g. make a website so I can see the temperature and humidity from anywhere with Wifi). The first thing I will do is arrange the components I need and figure out the connections from there. 

I connected the screen to pins 21 and 22, because I did some research before and learnt that D21 and D22 are commonly used as the default I2C pins (which the screen is).

I made my first draft for my firmware, however I am getting errors to do with the DHT Library. I will try to figure out what is wrong and fix it.

---

## Jul 8, 2026, 9:49 PM

I am still struggling to find the error. It says that the DHT sensor library isn't installed (when it is), so I am very confused at the moment.

Still struggling, I have no idea what the problem is.

I'm going to test just the DHT sensor in a test firmware, to see if that helps me identify the problem at all.

It works in my test file, so I must've done something wrong before, I will check through it.

I found the problem. I missed a single semicolon after "Adafruit_SSD1306 display(screenWidth,screenHeight, &Wire, -1)". That was fun.

I've got my screen to work, but the temperature and humidity shown are just random numbers? I will do my best to figure out why this is happening.

I suddenly got the idea to add a button that, when pressed, cycles through temperature and humidity (e.g. initially just temp on screen, press button, and now humidity on screen), so I will try to implement that.

After trying to add the button, now I'm getting the error "'display' does not name a type". Hopefully this fix is as simple as the last one.

It was a simple fix, I accidentally put it outside of the {} of updateDisplay, now I need to get my button to work.

The button works, but the numbers are still random.

---

## Jul 9, 2026, 11:31 AM

I am going to try fix the issue where the screen's output does not match up with the DHT11 sensor (random numbers).

The humidity seems to work correctly between 20 and 25%, but then at 26%, it shows 1.4%, at 27% its 2.4%, etc. Happens again at 51% = 26.4%, 52% = 2.8%.

Temperature is still sort of all over the place.

At least I sort of have identified the problem with the humidity sensor, I think it some sort of integer overflow error. I will go have lunch and come back to hopefully fix this problem, then I can start to tackle the temperature problem aswell.

---

## Jul 10, 2026, 11:55 AM

I have managed to get the humidity to work up to 44%, now I have to think about how to get it to work up to 90%.

I'm going to ask in #breadboard-help to see if anyone else can help me.

I've just realised that the temperature pattern is as follows:
0,1,2,3,4,5,...
0.0,1.0,0.4,1.4,0.8,...
which COULD help me think of an idea (still quite confused).

---

## Jul 10, 2026, 12:05 PM

After asking for help in #breadboard-help, apparently the error was that the editor treated the sensor as a DHT22, not a DHT11, and hopefully it will be fixed now, so I'm going to test it now.

Upon testing the error does seem to be fixed. My project does work, however I'm going to see if I can make it so that the humidity/temperature readings are always in the center of the screen.

Actually nevermind, I have already spent quite a lot of time on this and I'm happy with it as is. I think it is ready to publish.
