# Python3 program to draw solid-colored
# image using numpy.zeroes() function
import numpy as np
import cv2
  
# Creating a black image with 3 channels
# RGB and unsigned int datatype
img = np.zeros((400, 400, 3), dtype = "uint8")

# Creating line
#cv2.line(img, (20, 160), (100, 160), (0, 0, 255), 10)

# Creating rectangle
#cv2.rectangle(img, (30, 30), (300, 200), (0, 255, 0), 5)

# Creating circle
#cv2.circle(img, (200, 200), 80, (255, 0, 0), 3)

 # writing text
font = cv2.FONT_HERSHEY_SIMPLEX
cv2.putText(img, 'MIECT-LFA-2S-2021', (50, 50),
            font, 0.8, (0, 255, 0), 2, cv2.LINE_AA)

cv2.imshow('dark', img)
  
# Allows us to see image
# untill closed forcefully
cv2.waitKey(0)
cv2.destroyAllWindows()
  
# Allows us to see image
# untill closed forcefully
cv2.waitKey(0)
cv2.destroyAllWindows()