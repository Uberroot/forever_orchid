# Forever Orchid
Arduino project for a self watering plant. It's just annoying enough that you can't forget about it! The original intent was to create an orchid that can't be watered incorrectly but I think other plants like water as well.

# Wiring
* Connect a moisture sensor to an analog input for taking soil readings. A capacitive sensor is probably the best choice for longevity.
* Connect a water level sensor to an analog input for checking the tank for water. This is necessary to alert when the tank needs to be refilled and to keep the pump from running while dry.
* Connect a pot to an analog input to become the watering threshold setting.
* Connect a pot to an analog input to become the amount-per-watering attempt setting.
* Connect a piezo speaker to one of the digital outputs to become an alert for the user to refill the tank.
* Connect a bicolor 2-lead LED across two of the digital outputs to provide a status light.
* Connect a pump circuit to one of the digital outputs. Depending on the pump, a transistor switching main power bus may be sufficent as an ATMEGA won't provide enough power on it's own to run a pump.

# Configuring / Building
See defs.h for matching the inputs and outputs to the physical configuration chosen. Setting the water level sensor correctly may require some tuning to match the sensor, which can also be done from defs.h

When first setting up for the plant, turn the water threshold pot all the way up and turn the water timing pot all the way down. With the plant at the point it needs to be watered, insert the soil moisture sensor. Gradually turn the water threshold down until the pump begins to run. Gradually turn up the water timing pot until it *just* spits water through the tubing.

# Usage
Fill the water resevior, put the sensor in the plant, and run tubing for the water. That's it!
If the piezo is beeping / the LED is blinking red, the resevior needs water.
If the LED is solid green, it is in a watering cycle but the pump has paused to allow water to soak towards the moisture sensor.
If the LED is blinking green, the pump is active.

# Tips
* Add wiring_test() to setup() to test your connections and report values over serial.
* Keep the tip of the water tube above the plant and the water resevior, otherwise you might have a siphon that dumps the entire tank (depending on the pump used). This was learned the hard way with a USB aquarium pump.
* Put the light somewhere visible.
* Keep an eye on your plant after setting this up in case something needs to be tweaked. Not responsible for a dead plant.

# Pull Requests Welcome
