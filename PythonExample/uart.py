print("Hellow Sensors")
import serial.tools.list_ports
import time


def getPort():
    ports = serial.tools.list_ports.comports()
    N = len(ports)
    commPort = "None"
    for i in range(0, N):
        port = ports[i]
        strPort = str(port)
        if "USB-SERIAL CH340" in strPort: #tùy theo tên port trên PC
            splitPort = strPort.split(" ")
            commPort = (splitPort[0])
    # return commPort
    #return "COM3"
    return "COM4"
    #return "COM7"


portName = getPort()

if portName != "None":
    global ser
    ser = serial.Serial(port=portName, baudrate = 115200)
    print(ser)

mess = ""


def processData(client, data):
    data = data.replace("!", "")
    data = data.replace("#", "")
    splitData = data.split(":")
    print(splitData)
    if splitData[1] == "RT":
        client.publish("TempSensor", splitData[2])
    if splitData[1] == "RH":
        client.publish("HumiSensor", splitData[2])
    if splitData[1] == "LUX":
        client.publish("LightSensor", splitData[2])
    return 1    

read_time = 0

def readSerial(client):
    bytesToRead = ser.inWaiting()
    if (bytesToRead > 0):
        global mess
        mess = mess + ser.read(bytesToRead).decode("UTF-8")
        while ("#" in mess) and ("!" in mess):
            start = mess.find("!")
            end = mess.find("#")
            global read_time
            if(read_time < 2):
                read_time = read_time + processData(client, mess[start:end + 1])
            if (end == len(mess)):
                mess = ""
            else:
                mess = mess[end + 1:]

def writeData(data):
    global ser
    ser.write(str(data).encode())
    