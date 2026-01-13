import cellular
from machine import Pin, Timer
import time
from umqtt.robust import MQTTClient

cellular.gprs("wap","","")

DATA_FEED_ID = 'data'


ADAFRUIT_IO_URL= 'io.adafruit.com'
ADAFRUIT_USERNAME = 'fazleyelehi'
ADAFRUIT_IO_KEY = 'aio_WBwy35492K8aDtHCV69jODfeDeJF'
mqtt_client_id = bytes('test_'+'123456','utf-8')

client = MQTTClient(client_id=mqtt_client_id, 
                    server=ADAFRUIT_IO_URL, 
                    user=ADAFRUIT_USERNAME, 
                    password=ADAFRUIT_IO_KEY,
                    ssl=False)

try:            
    client.connect()
except Exception as e:
    print('could not connect to MQTT server {}{}'.format(type(e).__name__, e))
    sys.exit()
    
data_feed = bytes('{:s}/feeds/{:s}'.format(ADAFRUIT_USERNAME, DATA_FEED_ID), 'utf-8')

def send_data():
    client.publish(temp_feed,bytes(str(data),'utf-8'),qos=0)
    

timer = Timer(0)
timer.init(period=6000, mode=Timer.PERIODIC, callback = sens_data)

