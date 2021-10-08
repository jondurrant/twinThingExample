#Example Twin Observer, print state on change
#Jon Durrant
#27-Sep-2021


from twinObserver import TwinObserver
from twin import Twin
import json

#Example Twin Observer - just print state
class ExampleTwinObserver(TwinObserver):
    
    #Notification of change of Twin reported state.
    def notify(self, twin : Twin):
         print("twin: %s"% json.dumps(twin.getState()))
