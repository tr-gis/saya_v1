import roslib
import rospy
import smach
import smach_ros
import os, sys
from std_msgs.msg import Bool
from sound_play.msg import SoundRequest

from sound_play.libsoundplay import SoundClient
from std_msgs.msg import Int32
i=0

class Map3(smach.State):
	def __init__(self):
		smach.State.__init__(self, outcomes=['complete']) # Outcome

	def callback(self,data):
		rospy.logerr("Success %d",i)	

	def listener(self):
		global i
		try:	
			k=rospy.wait_for_message("ui_rating", Int32, timeout=10)
			rospy.Subscriber("ui_rating", Int32, self.callback)
			i=k.data 
		except(rospy.ROSException), e:
			rospy.logerr("No publish")
		rospy.logerr(i)


	def execute(self, userdata):
		global i
		self.listener()	
		return 'complete'
		
