
import roslib
import rospy
import smach 
import smach_ros
import os 
from std_msgs.msg import Int32

class screen1(smach.State):
	def __init__(self):
		smach.State.__init__(self, outcomes=['complete']) # Outcome
		
		
	def talker(self):
		pub = rospy.Publisher('ui_show_menu', Int32, queue_size=1)
		
		rate = rospy.Rate(1) # 10hz
		i=1
		while i<=1:
			hello_str = 1
			rospy.loginfo(hello_str)
			rospy.sleep(1)
			pub.publish(hello_str)			
			rate.sleep()
			i=i+1
			

	def execute(self, userdata):
		self.talker()	
		return 'complete'
