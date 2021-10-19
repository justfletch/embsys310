## Mysa Smart Thermostat

The device example I've chosen is a Mysa smart thermostat for high voltage (110-240VAC) in home heaters. I have three of them in my home. These are interesting to me because they use a ESP32 microcontroller inside. The earlier version that I have also has an afterthought addition of a decoupling capacitor placed on top of the microcontroller's solder pads.

![MYSA's ESP32 Decoupling Capacitor](../../assets/mysa_esp32.jpg)

Manufacturer's website: https://shop-us.getmysa.com/products/mysa-baseboard

Some of the functions and challenges for this device:

### Customer Controlled Setup
The customer must set it up on their own Wi-Fi network without plugging anything into the device, other than power. This requires a method for connecting to the device before it has any information about the customer's Wi-Fi network. The solution for this is that the device broadcasts its own Wi-Fi network during the setup stage. It has to work seamlessly with the Mysa smartphone app connection process: allowing the phone to connect to the device's network, transferring network data of the customer's network, stop broadcasting the device's network, then connecting to the customer's network. A difficulty with this process is how it should recover when the device cannot connect to the customer's Wi-Fi. It's likely that the device will keep resorting to broadcasting its own network until it has a successful connection to the customer's network. After that, failure to connect to the customer's network may be due to Wi-Fi issues, so it should periodically re-attempt connection instead of falling back to the setup process.

### Safety
This device is connected directly to and controlling a heater that is at line voltage. It must pass safety testing for home use. It should also have some ability to detect if the built-in temperature sensor is functioning correctly. The temperature should see some measurable change after the heater is active for some amount of time. There is also a risk of the temperature setting being set too high, possibly creating a dangerous environment for pets or humans. For this, the smartphone app seems to limit the device to selectable minimum and maximum temperature values. These values are selected in a settings menu, outside of the typical temperature adjustment controls. The selectable values are limited to a list of pre-selected values between 41-86°F. I'm not sure if those values are limited by the smartphone app or by the device itself.

### Security
Since this device is connected to the internet, it must have some level of security to prevent unauthorized access. 

### Physical User Interface
In addition to control over the network from the smartphone app, there are a few capacitive touch buttons to adjust the temperature. The response from interacting with the buttons must be adequate for a typical user, so may require some priority over other tasks. There is an LED grid that displays the temperature in two digits [70]. 

### Scheduling
It's not clear where this is controlled, though I would expect a set schedule (heat to 68°F in the mornings from 7-9AM, evenings from 7-11PM for M-F, etc.) to be saved to the controller itself. If there is a network outage, this shouldn't interrupt the heating of someone's home as long as there is still power. So, the device must store the schedule settings that the smartphone app provides to it, and operate with some level of time keeping accuracy when there is no network connection to provide the current date/time.

### Control Algorithm(s)
The device claims to use a more complicated algorithm for maintaining a desired temperature, instead of using a typical hysteresis control function. So the device then has to gain some more information abou the room's response time. This is supposedly useful for a less active on/off cycle.

### Testing
There are multiple systems that must be tested for this device:

* Communication with the smartphone app, probably different versions of the app (Android, Apple), and different device & app revisions
* Network connection reliability
* Recovery from network outage/instability
* Network security
* Temperature sensing accuracy & reliability
* Heater control, for different manufacturer's, voltage levels.
* Human interface buttons/display
* Control Algorithm(s)
* Recovery from power outage