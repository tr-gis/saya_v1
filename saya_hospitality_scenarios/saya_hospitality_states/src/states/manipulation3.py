import roslib
import rospy
import smach
import smach_ros
import os, sys
from std_msgs.msg import Bool
from sound_play.msg import SoundRequest
from std_msgs.msg import Int32

from sound_play.libsoundplay import SoundClient


class Arm_Manipulation3(smach.State):
	def __init__(self):
		smach.State.__init__(self, outcomes=['Executed']) # Outcome

	def talker(self):
		pub = rospy.Publisher('ui_nav_finish', Int32, queue_size=1)
		
		rate = rospy.Rate(1) # 10hz
		i=1
		while i<=1:
			hello_str = 1
			rospy.loginfo(hello_str)
			rospy.sleep(0.1)
			pub.publish(hello_str)
			rate.sleep()
			i=i+1

	
	def execute(self, userdata):
		
		os.system("roslaunch eva_arm_controller play3.launch") # launches the play back file

		self.talker()
		
			
		return 'Executed'
	
