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
from topicStats import TopicStats




print("Go")
while True:
    try:
        with Serial('/dev/ttyS0', 9600, timeout=0.02) as ser:
            
            twin : Twin = TwinSerial(ser)
            twinObs: ExampleTwinObserver = ExampleTwinObserver();
            twin.attach(twinObs)

            ping : TopicPing = TopicPing()
            twin.addTopic("ping", ping)
            twin.addTopic("pong", ping)
            
            stats : TopicStats = TopicStats()
            twin.addTopic("stats", stats)
            
            twin.start()
            
            while True:    
                for i in range(100):         
                    
                    #Request full state of object
                    if (i == 1):
                        twin.publishMsg("get", "")
                        
                    #Ping topic
                    if (i == 30):
                        twin.publishMsg("ping", "")  
        
                    #Switch light on or off
                    if (i == 60):
                        on = True
                        if ("on" in twin.getState().keys()):
                            on = not(twin.getState()["on"])
                        update = { "on": on }     
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
                        
                        
                    #Ping topic
                    if (i == 95):
                        twin.publishMsg("stats", "")
                        print("Stats request")
                        
                    time.sleep(0.1)
                    
    except SerialException as ex:
        print("Reloading")
        time.sleep(2)
    
