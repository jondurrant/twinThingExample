from serial import Serial
from serial import SerialException
import io
import time

import json

from twin import Twin
from twinSerial import TwinSerial
from random import randint

from topicPing import TopicPing
from exampleTwinObserver import ExampleTwinObserver




print("Go")
while True:
    try:
        with Serial('/dev/ttyACM0', 192000, timeout=0.02) as ser:
            
            twin : Twin = TwinSerial(ser)
            twinObs: ExampleTwinObserver = ExampleTwinObserver();
            twin.attach(twinObs)

            ping : TopicPing = TopicPing()
            twin.addTopic("ping", ping)
            
            while True:    
                for i in range(100):          
                    twin.readLine()
        
        
                    #Switch light on or off
                    if (i == 60):
                        update = { "on": not(twin.getState()["on"])
                            }    
                        twin.updateState(update)
                        if (update["on"]):
                            print("LED ON")
                        else:
                            print("LED OFF")
                        
                    #Chante to random colour
                    if (i == 90):
                        print("Change colour")
                        update = {
                                "rgb": [randint(0, 0xff), randint(0, 0xff), randint(0, 0xff)]
                                }
                        twin.updateState(update)
                        
                        
                    #Request full state of object
                    if (i == 1):
                        twin.publishMsg("get", "")
                        
                    #Ping topic
                    if (i == 30):
                        twin.publishMsg("ping", "")
                        
                    
    except SerialException as ex:
        print("Reloading")
        time.sleep(2)
    
