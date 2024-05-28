import cv2
import urllib.request
import numpy as np

url='http://192.168.0.104:8080/shot.jpg'
#cam=cv2.VideoCapture() #/another way to cast cameraq
while True:

    #image decoding from url open>convert to byte>decode as image
    imgurl=urllib.request.urlopen(url)
    
    imgnp=np.array(bytearray(imgurl.read()),dtype=np.uint8)
    
    cam=cv2.imdecode(imgnp,-1)
    camR=cv2.resize(cam,(640,360))

 ##showing image via imshow------------
    cv2.imshow('android cam',camR)
    
    if cv2.waitKey(1) & 0xff ==ord('q'):
        break
cam.release()