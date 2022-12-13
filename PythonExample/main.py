print("Hello IoT Python")
import sys
from Adafruit_IO import MQTTClient
import random
import time
# from simple_ai import *
import uart
import os



AIO_FEED_ID = ["nutnhan1", "nutnhan2"]
AIO_USERNAME = "thoriumrabbit02"
AIO_KEY = "aio_GqDP12LRkjQxWf7wWd734rx4kDwK"

def connected(client):
    print("Ket noi thanh cong ...")
    for id in AIO_FEED_ID:
        client.subscribe(id)

def subscribe(client , userdata , mid , granted_qos):
    print("Subscribe thanh cong ...")

def disconnected(client):
    print("Ngat ket noi ...")
    sys.exit (1)

def message(client , feed_id , payload):
    print("Data is from: " + feed_id + ", Payload: " + payload)
    if feed_id == "nutnhan1":
        if payload == "0":
            uart.writeData('!1:LED0:0#')
        else: 
            uart.writeData('!1:LED0:1#')
    if feed_id == "nutnhan2":
        if payload == "1":
            uart.writeData('!1:LED1:0#')
        else: 
            uart.writeData('!1:LED1:1#')   
                 
client = MQTTClient(AIO_USERNAME , AIO_KEY)
client.on_connect = connected
client.on_disconnect = disconnected
client.on_message = message
client.on_subscribe = subscribe
client.connect()
client.loop_background()

    

counter_sensor = 15
counter_ai = 5


while True:
    if (os.system("ping -n 1 " + "io.adafruit.com" + ">/null") == False):
        uart.readSerial(client)
        counter_sensor = counter_sensor - 1
        if counter_sensor <= 0:
            uart.readSerial(client)
            uart.read_time = 0
            counter_sensor = 8
            print("----------------")

        counter_ai = counter_ai - 1
        if counter_ai <= 0:    
            counter_ai = 8
            # image_capture()
            #ai_result = image_detector()
            #ai_split = ai_result.split(" ")
            # client.publish("visiondetection", ai_split[1])
    else:
        print("Adafruit Disconnected")
        if (os.system("ping -n 1 " + "io.adafruit.com" + ">/null") == False):
            print("Adafruit Reconnected")
            client.connect()
        time.sleep(10)
    time.sleep(1)        
    pass
