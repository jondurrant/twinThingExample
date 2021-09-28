# twinThingExample
Example Raspberry PICO IOT or Digital Twin project using twinThing library

Simple example of using the library to sync state with a Raspberry PICO as thing
device over USB. Code was written to run on a Raspberry PI, you may need to change
the USB serial devices for other hosts

Code simulates holding RGB colours of a light and then turns on and off the light.
In reality it only turns on the onboard lED on the Raspberry PICO.

The PICO also keeps sending it's tempurate back as part of it's state to the 
host or digital twin.

More on the design of the [library repo](+[twinThing](https://github.com/jondurrant/twinThing)


# Depenencies
## C Dependencies
Communication is all in JSON format and use JSON libraries from rafagafe.

+[json-maker](https://github.com/rafagafe/json-maker)

+[tiny-json](https://github.com/rafagafe/tiny-json)

+[twinThing](https://github.com/jondurrant/twinThing)

## Python3 Dependencies
+[twinThing](https://github.com/jondurrant/twinThing)

Using PYTHONPATH to pick up the modules rather than packaging


