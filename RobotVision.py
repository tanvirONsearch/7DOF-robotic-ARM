import cv2
import numpy as np
import schedule
import time
import urllib.request
import serial

####for opening ip web cam link
url='http://192.168.0.109:8080/shot.jpg'

##########For sending data to arduino
comport='com4'
rate=115200
arduino=serial.Serial(comport,rate)

def write_arduino():
    time.sleep(1)
    print("Inside Arduino write function")
    bc=[44,47]
    if  all(item in classIds for item in bc):
         mssg="a"
         mssg=mssg+'\r'
         arduino.write(mssg.encode())
         
         print("bottle+cup")
    elif 44 in classIds:
        mssg="b"
        mssg=mssg+'\r'
        arduino.write(mssg.encode())
        
        print("bottle")
    elif 47 in classIds:
         mssg="c"
         mssg=mssg+'\r'
         arduino.write(mssg.encode())
         
         print("cup")

schedule.every(2).seconds.do(write_arduino)




############### Object detection part 
classNames=[]
classFile='Projects/Model/coco.names'
with open(classFile,'rt') as f:
    classNames=f.read().rstrip('\n').split('\n')

configPath='Projects/Model/ssd_mobilenet_v3_large_coco_2020_01_14.pbtxt'
weightPath='Projects/Model/frozen_inference_graph.pb'

net=cv2.dnn_DetectionModel(weightPath,configPath)
net.setInputSize(640,360)
net.setInputScale(1.0/127.5)
net.setInputMean((127.5,127.5,127.5))
net.setInputSwapRB(True)

while True:

    schedule.run_pending()
    
    #image decoding from url open>convert to byte>decode as image
    imgurl=urllib.request.urlopen(url)
    imgnp=np.array(bytearray(imgurl.read()),dtype=np.uint8)
    image=cv2.imdecode(imgnp,-1)
    image=cv2.resize(image,(640,360))

    classIds,confs,bbox=net.detect(image,confThreshold=0.6)


    bc=[44,47]
    if  all(item in classIds for item in bc):
         print("bottle+cup")
    elif 44 in classIds:       
        print("bottle")
    elif 47 in classIds:      
        print("cup")
    
    ##computer vision part
    if len(classIds)!=0:
        for classID,confs,box in  zip(classIds.flatten(),confs.flatten(),bbox):
                cv2.rectangle(image,box,color=(0,255,0),thickness=2)
                cv2.putText(image,classNames[classID-1].upper(),(box[0]+10,box[1]+30),
                            cv2.FONT_HERSHEY_DUPLEX,1,(0,255,0),1)


 ##showing image via imshow------------
    cv2.imshow('android cam',image)
    
    if cv2.waitKey(1) & 0xff ==ord('q'):
        break
        
image.release()
arduino.close()


