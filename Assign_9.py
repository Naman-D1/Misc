#this code was made on google collab. Comments show where one block ends, and another begins.

#Block 1: Image upload
from google.colab import files
import io

print("Please upload your image file:")
uploaded = files.upload()

for filename in uploaded.keys():
    print(f'User uploaded file "{filename}" with length {len(uploaded[filename])} bytes')
    # Assuming you want to use the first uploaded file, or specify if multiple are uploaded
    # To make sure the image is saved to the working directory
    with open(filename, 'wb') as f:
        f.write(uploaded[filename])

# Update imagePath to the name of the uploaded file
# If you uploaded multiple files, you'll need to specify which one you want to use.
# For simplicity, we'll assume a single image upload or use the first one if multiple are given.
if uploaded:
    first_uploaded_filename = list(uploaded.keys())[0]
    imagePath = first_uploaded_filename
    print(f"Updated imagePath to: {imagePath}")
else:
    print("No file uploaded. Please upload an image to proceed.")

#==============================================================================================================================

#Block 2: Facial Recognition
import cv2
import matplotlib.pyplot as plt
%matplotlib inline

import os
import sys

# imagePath="<image>.jpg" # This line is commented out to use the globally set imagePath
cascPath="haarcascade_frontalface_default.xml"

# Ensure the Haar cascade XML file is present
if not os.path.exists(cascPath):
    print(f"'{cascPath}' not found. Attempting to download it.")
    url = "https://raw.githubusercontent.com/opencv/opencv/master/data/haarcascades/haarcascade_frontalface_default.xml"
    try:
        # Use !wget for convenience in Colab
        !wget -q -O {cascPath} {url}
        print(f"Successfully downloaded '{cascPath}'.")
    except Exception as e:
        print(f"Error downloading '{cascPath}': {e}")
        # If download fails, the CascadeClassifier creation will likely fail
        # Consider adding sys.exit(1) here for critical failures

# Initialize the CascadeClassifier
faceCascade = cv2.CascadeClassifier(cascPath)

# Check if the cascade classifier was loaded successfully
if faceCascade.empty():
    print(f"Error: Could not load cascade classifier from '{cascPath}'.")
    print("This might be due to a corrupted XML file, an incorrect path, or an issue with your OpenCV installation.")
    # If the AttributeError truly means the attribute doesn't exist, this check won't be reached.
    # But if the AttributeError is a symptom of failed initialization, this check could be useful.
    # sys.exit(1) # Consider exiting if it's critical.

# Ensure the image loads correctly. The provided imagePath is a placeholder.
image= cv2.imread(imagePath)
if image is None:
    print(f"Error: Could not load image from '{imagePath}'. Please ensure the image file exists and the path is correct.")
    # Further operations will fail if the image is not loaded.
    # For a robust script, you might want to exit or handle this more gracefully.
    sys.exit(1) # Exit if image cannot be loaded.

gray= cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

RGB_img= cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

plt.imshow(RGB_img)
plt.show()

faces= faceCascade.detectMultiScale(
    gray,
    scaleFactor= 1.01,
    minNeighbors=15, # Corrected from minNeighbours
    minSize=(2,2),
    flags= cv2.CASCADE_SCALE_IMAGE
    #flags= cv2.cv.CV_HAAR_SCALE_IMAGE
)

print("Found {0} faces!".format(len(faces)))

for (x,y,w,h) in faces:
  cv2.rectangle(image, (x,y), (x+w, y+h), (0,255,0), 2)

RGB_img= cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
plt.imshow(RGB_img)
plt.show()