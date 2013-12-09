#!/usr/bin/env python

from subprocess import Popen, PIPE
import roslib
roslib.load_manifest('ar_pose')
import rospy
from std_msgs.msg import String
from ar_pose.msg import ARMarker
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import cv


class TagDetector:

    def __init__(self):
        rospy.init_node('tag_detector', anonymous=True)
        
	# Publishers
	self.pub = rospy.Publisher('/qrcode', String)

	# Subscribers
        rospy.Subscriber("/usb_cam/image_raw", Image, self.image_received_callback)
        rospy.Subscriber("/ar_pose_marker", ARMarker, self.marker_detected_callback)

    # main loop
    def loop(self):
        while not rospy.is_shutdown():
            rospy.sleep(1.0)


    # callback fired when a marker has been detected
    # Searches for a qrcode in the image, if it finds one, it publishes it in the /qrcode topic
    def marker_detected_callback(self, data):
    	output = Popen("zbarimg -q camera.jpg", shell=True, stdout=PIPE).communicate()[0]
    	output = output.rstrip('\r\n')
    	output = output.replace("QR-Code:", "")
    	if output <> "":
            	self.pub.publish(String(output))

    # callback fired when an image has been received from the topic "image_raw"
    def image_received_callback(self, data):
    	cv_image = CvBridge().imgmsg_to_cv(data, "bgr8")
        # Saves the image in order to process it with zbarimg
    	cv.SaveImage("camera.jpg", cv_image)


if __name__ == '__main__':
    detector = TagDetector()
    detector.loop()
